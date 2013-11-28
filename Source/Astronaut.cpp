#include "Astronaut.h"
#include "Being.h"
#include "ResourceHolder.h"
#include "Utility.h"
#include "TextNode.h"

#include <string>

const float SCALE = 30.f; // Box2D works in a scale of 30 pixels = 1 meter

Astronaut::Astronaut(Type type, const TextureHolder& textures, const FontHolder& fonts, b2World& world):
    Being(type, textures, fonts, world)
{
}

void Astronaut::thrusterUp()
{
    if (m_body->GetLinearVelocity().y * SCALE < 300)
        m_body->ApplyForce(b2Vec2(0, m_body->GetMass()*25), m_body->GetWorldCenter());
}

void Astronaut::thrusterDown()
{
    if (m_body->GetLinearVelocity().y * SCALE > -300)
        m_body->ApplyForce(b2Vec2(0, -m_body->GetMass()*25), m_body->GetWorldCenter());
}

void Astronaut::thrusterLeft()
{
    if (m_body->GetLinearVelocity().x * SCALE < 300)
        m_body->ApplyForce(b2Vec2(m_body->GetMass()*10, 0), m_body->GetWorldCenter());
}

void Astronaut::thrusterRight()
{

    if (m_body->GetLinearVelocity().x * SCALE > -300)
        m_body->ApplyForce(b2Vec2(-m_body->GetMass()*10, 0), m_body->GetWorldCenter());
}

