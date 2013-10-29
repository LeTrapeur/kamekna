#include "Entity.h"

const float SCALE = 30.f; // Box2D works in a scale of 30 pixels = 1 meter

Entity::Entity(b2World& world):
    m_body(nullptr)
{}

void Entity::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
}

void Entity::updateCurrent(sf::Time dt)
{
    setPosition(m_body->GetPosition().x * SCALE, m_body->GetPosition().y * SCALE);
    setRotation(m_body->GetAngle()*pi()/180);
}

void Entity::setPosition(float x, float y)
{
    sf::Transformable::setPosition(x,y);
    m_body->SetTransform(b2Vec2(x/SCALE, y/SCALE), m_body->GetAngle());
}

void Entity::setRotation(float angle)
{
    sf::Transformable::setRotation(angle);
    m_body->SetTransform(b2Vec2(sf::Transformable::getPosition().x/SCALE, sf::Transformable::getPosition().y/SCALE), (angle*pi())/180);
}
