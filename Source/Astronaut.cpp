#include "Astronaut.h"
#include "Actor.h"
#include "ResourceHolder.h"
#include "Utility.h"
#include "TextNode.h"

#include <string>

// TODO Vitesse max

const float SCALE = 30.f; // Box2D works in a scale of 30 pixels = 1 meter

Astronaut::Astronaut(Type type, const TextureHolder& textures, const FontHolder& fonts, b2World& world):
    Actor(type, textures, fonts, world),
    m_power(100.f),
    m_powerRecoveryTime(sf::seconds(3.f)),
    m_isThrusting(false),
    m_powerDisplay(nullptr)
{
    if(type != Actor::Hero)
    {
        std::unique_ptr<TextNode> powerDisplay(new TextNode(fonts, (std::to_string(m_power) + " PW")));
        powerDisplay->setPosition(0.f, -50.f);
        m_powerDisplay = powerDisplay.get();
        attachChild(std::move(powerDisplay));
    }

    m_powerRecovery.restart();
}

void Astronaut::thrusterUp()
{
    if (m_body->GetLinearVelocity().y * SCALE < 300 && m_power)
        m_body->ApplyForce(b2Vec2(0, m_body->GetMass()*25), m_body->GetWorldCenter());

    m_isThrusting = true;
}

void Astronaut::thrusterDown()
{
    if (m_body->GetLinearVelocity().y * SCALE > -300 && m_power)
        m_body->ApplyForce(b2Vec2(0, -m_body->GetMass()*25), m_body->GetWorldCenter());

    m_isThrusting = true;
}

void Astronaut::thrusterLeft()
{
    if (m_body->GetLinearVelocity().x * SCALE < 300 && m_power)
        m_body->ApplyForce(b2Vec2(m_body->GetMass()*10, 0), m_body->GetWorldCenter());

    m_isThrusting = true;
}

void Astronaut::thrusterRight()
{
    if (m_body->GetLinearVelocity().x * SCALE > -300 && m_power)
        m_body->ApplyForce(b2Vec2(-m_body->GetMass()*10, 0), m_body->GetWorldCenter());

    m_isThrusting = true;
}

float Astronaut::getPower() const
{
    return m_power;
}

void Astronaut::checkThrusters()
{
    if(m_isThrusting)
    {
        m_powerRecovery.restart();
        m_power--;
    }
    else if(m_powerRecovery.getElapsedTime() > m_powerRecoveryTime)
    {
        m_power++;
    }

    if(m_power < 0)
        m_power = 0;
    if(m_power > 100)
        m_power = 100;

    m_isThrusting = false;

    if(m_powerDisplay)
        m_powerDisplay->setString(std::to_string(m_power) + " PW");
}

void Astronaut::updateCurrent(sf::Time dt)
{
    checkThrusters();
    Entity::updateCurrent(dt);
}
