#include "World.h"

int numFootContacts = 0;
const float SCALE = 30.f; // Box2D works in a scale of 30 pixels = 1 meter

World::World(sf::RenderWindow& window):
    m_window(window),
    m_worldView(window.getDefaultView()),
    m_minimapView(window.getDefaultView()),
    m_physicWorld(b2Vec2(0, 15.0f)),
    m_worldBounds(
                  -1280,
                  -720,
                  3840,
                  2160
                  ),
    m_player(nullptr)
{
    m_minimapView.zoom(4.0f);
    m_minimapView.setViewport(sf::FloatRect(0.85f, 0.f, 0.15f, 0.15f));
    m_physicWorld.SetContactListener(&m_contactListener);
    buildScene();
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

    for(int i=0; i < 5; i++)
    {
        std::unique_ptr<Platform> tempPlatform(new Platform(m_physicWorld));
        tempPlatform->setPosition(100.f, i*500.f);
        m_sceneLayers[Space]->attachChild(std::move(tempPlatform));
    }

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
    // Update physic
    m_physicWorld.Step(dt.asSeconds(), 8, 4);

    m_sceneGraph.update(dt);
}

void World::draw()
{
    m_worldView.setCenter(m_player->getPosition());
    m_window.setView(m_worldView);
    m_window.draw(m_sceneGraph);

    m_minimapView.setCenter(m_player->getPosition());
    m_window.setView(m_minimapView);
    m_window.draw(m_sceneGraph);
}
