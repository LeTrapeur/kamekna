#include "World.h"

int numFootContacts = 0;
const float SCALE = 30.f; // Box2D works in a scale of 30 pixels = 1 meter

World::World(sf::RenderWindow& window):
    m_window(window),
    m_worldView(window.getDefaultView()),
    m_minimapView(window.getDefaultView()),
    m_physicWorld(b2Vec2(0, 15.0f)),
    m_entities(),
    m_player(nullptr)

{
    m_minimapView.zoom(4.0f);
    m_minimapView.setViewport(sf::FloatRect(0.85f, 0.f, 0.15f, 0.15f));
    m_physicWorld.SetContactListener(&m_contactListener);
    buildScene();
}

void World::buildScene()
{
    std::unique_ptr<Platform> tempPlatform(new Platform(m_physicWorld));
    tempPlatform->setPosition(50, 500);
    m_entities.push_back(std::move(tempPlatform));

    std::unique_ptr<Hero> tempLadral(new Hero(m_physicWorld));
    tempLadral->setPosition(60,450);
    m_player = tempLadral.get();
    m_entities.push_back(std::move(tempLadral));
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
    // Aplly physic to objects
    for(auto it = m_entities.begin(); it != m_entities.end(); it++)
        (*it)->update();
}

void World::draw()
{
    m_worldView.setCenter(m_player->getPosition());
    m_window.setView(m_worldView);
    for(auto it = m_entities.begin(); it != m_entities.end(); it++)
        m_window.draw(*(*it));

    m_window.setView(m_minimapView);
    for(auto it = m_entities.begin(); it != m_entities.end(); it++)
        m_window.draw(*(*it));
}
