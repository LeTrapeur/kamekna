#include "World.h"

#include <tmx/MapLoader.h>
#include <tmx/tmx2box2d.h>

#include "Actor.h"
#include "Astronaut.h"
#include "SpriteNode.h"
#include "SoundNode.h"
#include "Platform.h"
#include "Asteroid.h"
#include "Planet.h"

const float SCALE = 30.f; // Box2D works in a scale of 30 pixels = 1 meter

// TODO LEVEL
// TODO bug quand joueur meurt
World::World(sf::RenderWindow& window, FontHolder& fonts, SoundPlayer& sounds):
    m_window(window),
    m_fonts(fonts),
    m_sounds(sounds),
    m_worldView(window.getDefaultView()),
    m_minimapView(window.getDefaultView()),
    m_physicWorld(b2Vec2(0, 10.0f)),
    m_worldBounds(
                  0,
                  0,
                  3*1280,
                  3*720
                  ),
    m_player(nullptr),
    m_spawnPosition(100 ,500),
    m_commandQueue(),
    m_contactListener(m_commandQueue),
    m_ia(),
    ml("maps/")
{
    loadTextures();

    m_minimapView.zoom(4.0f);
    m_minimapView.setViewport(sf::FloatRect(0.85f, 0.f, 0.15f, 0.15f));
    m_minimapView.setCenter(m_spawnPosition);
    m_worldView.setCenter(m_spawnPosition);

    m_physicWorld.SetContactListener(&m_contactListener);

    buildScene();
}

void World::loadTextures()
{
    m_textures.load(Textures::SpaceBackground, "background.png");
    m_textures.load(Textures::Hero, "astronaut.png");
    m_textures.load(Textures::HeroAnim, "astronaut.anim.png");
    m_textures.load(Textures::Asteroid, "asteroid.png");
    m_textures.load(Textures::Enemy, "enemy.png");
    m_textures.load(Textures::Bullet, "bullet.png");
    m_textures.load(Textures::Metal, "metal.png");
}

void World::buildScene()
{

    // Init layers
    for(std::size_t i = 0; i < LayerCount; ++i)
    {
        Category::Type category = (i == Space) ? Category::UpperScene : Category::None;
        SceneNode::Ptr layer(new SceneNode(category));
        m_sceneLayers[i] = layer.get();
        m_sceneGraph.attachChild(std::move(layer));
    }
    // SoundNode
    std::unique_ptr<SoundNode> soundNode(new SoundNode(m_sounds));
    m_sceneGraph.attachChild(std::move(soundNode));


	ml.Load("map.tmx");
	const std::vector<tmx::MapLayer>& layers = ml.GetLayers();
    for (const auto& l : layers)
	{
		if (l.name == "Static") //static bodies which make up the map geometry
		{
			for (const auto& o : l.objects)
			{
				std::cout << o.GetName() << " at: " << o.GetPosition().x << " " << o.GetPosition().y << " size: " << o.GetAABB().width << " " << o.GetAABB().height << std::endl;
                std::unique_ptr<Platform> platform(new Platform(o.GetAABB().width, o.GetAABB().height, tmx::BodyCreator::Add(o, m_physicWorld)));
                platform->setPosition(o.GetCentre().x, o.GetCentre().y); // TODO trouver origine
                m_sceneLayers[Space]->attachChild(std::move(platform));
			}
		}
	}

    // Hero
    std::unique_ptr<Astronaut> hero(new Astronaut(Actor::Hero, m_textures, m_fonts, m_physicWorld));
    m_player = hero.get();
    hero->setPosition(m_spawnPosition);
    m_ia.addPlayer(hero.get()); // ajout de la connaissance joueur à l'ia
    m_sceneLayers[Space]->attachChild(std::move(hero));


    // Enemy
    std::unique_ptr<Astronaut> enemy(new Astronaut(Actor::Enemy, m_textures, m_fonts, m_physicWorld));
    enemy->setPosition(200, 500);
    m_ia.addEnemy(enemy.get());
    m_sceneLayers[Space]->attachChild(std::move(enemy));

}

void World::update(sf::Time dt)
{
    while(!m_commandQueue.isEmpty())
        m_sceneGraph.onCommand(m_commandQueue.pop(), dt);

    m_ia.updateIA(dt, m_commandQueue);

    m_physicWorld.Step(dt.asSeconds(), 8, 4);
    m_sceneGraph.update(dt, m_commandQueue);

    adaptPlayerPosition();
    adaptScrolling();

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
    m_window.draw(ml);
    m_window.draw(m_sceneGraph);

    m_window.setView(m_minimapView);
    m_window.draw(ml);
    m_window.draw(m_sceneGraph);
}

CommandQueue& World::getCommandQueue()
{
    return m_commandQueue;
}

float World::getPlayerLife() const
{
    return m_player->getLife();
}

float World::getPlayerPower() const
{
    return m_player->getPower();
}

void World::updateSounds()
{
   m_sounds.removeStoppedSounds();
}
