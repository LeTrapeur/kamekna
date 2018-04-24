#include "World.hpp"

#include "Actor.hpp"
#include <FRK2D/SpriteNode.hpp>
#include <FRK2D/SoundNode.hpp>
#include <FRK2D/Platform.hpp>
#include <FRK2D/TiledMapNode.hpp>

#include <tmx/MapLoader.hpp>
#include <tmx/tmx2box2d.hpp>

const float SCALE = 30.f; // Box2D works in a scale of 30 pixels = 1 meter

// TODO LEVEL
World::World(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts, SoundPlayer& sounds):
    m_window(window),
    m_fonts(fonts),
    m_sounds(sounds),
    m_textures(textures),
    m_worldView(window.getDefaultView()),
    m_minimapView(window.getDefaultView()),
    m_physicWorld(b2Vec2(0, 0.0f)),
    m_worldBounds(
                  0,
                  0,
                  384,
                  192
                  ),
    m_player(nullptr),
    m_spawnPosition(m_worldBounds.left+m_worldBounds.width/2, m_worldBounds.top+m_worldBounds.height/2),
    m_commandQueue(),
    m_contactListener(m_commandQueue)
{

    m_worldView.setCenter(m_spawnPosition);

    m_physicWorld.SetContactListener(&m_contactListener);

    buildScene();
}

void World::loadTextures()
{

}

void World::buildScene()
{

    // Init layers
    for(std::size_t i = 0; i < LayerCount; ++i)
    {
        Category::Type category = (i == Foreground) ? Category::UpperScene : Category::None;
        SceneNode::Ptr layer(new SceneNode(category));
        m_sceneLayers[i] = layer.get();
        m_sceneGraph.attachChild(std::move(layer));
    }

    // Add the background sprite to the scene
    std::unique_ptr<TiledMapNode> tiledMap(new TiledMapNode());
    tiledMap->setPosition(m_worldBounds.left, m_worldBounds.top);
    m_sceneLayers[Layer::Background]->attachChild(std::move(tiledMap));

    // Add player
    std::unique_ptr<Actor> hero(new Actor(Actor::Hero, m_textures, m_fonts, m_physicWorld));
    m_player = hero.get();
    hero->setPosition(m_spawnPosition);
    m_sceneLayers[Layer::Foreground]->attachChild(std::move(hero));
}

void World::update(sf::Time dt)
{
    while(!m_commandQueue.isEmpty())
        m_sceneGraph.onCommand(m_commandQueue.pop(), dt);

    m_physicWorld.Step(dt.asSeconds(), 8, 4);
    m_sceneGraph.update(dt, m_commandQueue);

    updateSounds();

    m_sceneGraph.removeWrecks();
}

sf::Vector2f World::getMouseWorldPosition()
{
    sf::Vector2i pixelPos = sf::Mouse::getPosition(m_window);
    sf::Vector2f worldPos = m_window.mapPixelToCoords(pixelPos, m_worldView);
    return worldPos;
}

void World::adaptPlayerPosition()
{
    if(!(m_player->getPosition().x > m_worldBounds.left && m_player->getPosition().x < m_worldBounds.width + m_worldBounds.left && m_player->getPosition().y > m_worldBounds.top && m_player->getPosition().y < m_worldBounds.height + m_worldBounds.top))
    {
        m_player->setPosition(m_spawnPosition);
        m_player->resetForces();
    }
}

void World::adaptScrolling()
{
    // TODO limiter scrolling
    sf::Vector2f myscroll(m_player->getPosition());
    m_worldView.setCenter(myscroll);
    m_minimapView.setCenter(myscroll);
}

void World::draw()
{

    m_window.setView(m_worldView);
    m_window.draw(m_sceneGraph);
}

CommandQueue& World::getCommandQueue()
{
    return m_commandQueue;
}

void World::updateSounds()
{
   m_sounds.removeStoppedSounds();
}
