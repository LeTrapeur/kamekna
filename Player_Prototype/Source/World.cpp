#include "World.h"

const float SCALE = 30.f; // Box2D works in a scale of 30 pixels = 1 meter

World::World(sf::RenderWindow& window):
    m_window(window),
    m_worldView(window.getDefaultView()),
    m_minimapView(window.getDefaultView()),
    m_physicWorld(b2Vec2(0, 15.0f)),
    m_worldBounds(
                  -1280,
                  -720,
                  2*1280,
                  2*720
                  ),
    m_player(nullptr)
{
    loadTextures();

    m_minimapView.zoom(4.0f);
    m_minimapView.setViewport(sf::FloatRect(0.85f, 0.f, 0.15f, 0.15f));

    m_physicWorld.SetContactListener(&m_contactListener);

    buildScene();
}

void World::loadTextures()
{
    m_textures.load(Textures::SpaceBackground, "background.png");
}

void World::buildScene()
{
    // Init layers
    for(std::size_t i = 0; i < LayerCount; ++i)
    {
        SceneNode::Ptr layer(new SceneNode());
        m_sceneLayers[i] = layer.get();
        m_sceneGraph.attachChild(std::move(layer));
    }

    // background
    sf::Texture& texture = m_textures.get(Textures::SpaceBackground);
    sf::IntRect textureRect(m_worldBounds);
    texture.setRepeated(true);
    std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(texture, textureRect));
    backgroundSprite->setPosition(m_worldBounds.left, m_worldBounds.top);
    m_sceneLayers[Background]->attachChild(std::move(backgroundSprite));

    // platforms
    for(int i=0; i < 5; i++)
    {
        std::unique_ptr<Platform> tempPlatform(new Platform(m_physicWorld));
        tempPlatform->setPosition(100.f, i*500.f);
        m_sceneLayers[Space]->attachChild(std::move(tempPlatform));
    }

    // heroe
    std::unique_ptr<Hero> ladral(new Hero(m_physicWorld));
    m_player = ladral.get();
    ladral->setPosition(200,450);
    m_sceneLayers[Space]->attachChild(std::move(ladral));
}

// To be improved
Hero* World::getPtrPlayer()
{
    return m_player;
}

void World::update(sf::Time dt)
{
    if(m_player->getPosition().x > -1280 && m_player->getPosition().x < 1280
       &&
       m_player->getPosition().y > -720 && m_player->getPosition().y < 720)
    {
        m_physicWorld.Step(dt.asSeconds(), 8, 4);
        m_sceneGraph.update(dt);
    }
    else
    {
        m_player->setPosition(200,450);
    }

}

void World::draw()
{
    if(m_player->getPosition().x > -1280 && m_player->getPosition().x < 1280
       &&
       m_player->getPosition().y > -720 && m_player->getPosition().y < 720)
    {
        m_worldView.setCenter(m_player->getPosition());
        m_minimapView.setCenter(m_player->getPosition());
    }

    m_window.setView(m_worldView);
    m_window.draw(m_sceneGraph);

    m_window.setView(m_minimapView);
    m_window.draw(m_sceneGraph);
}
