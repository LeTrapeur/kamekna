#include "Entity.h"

const float SCALE = 30.f; // Box2D works in a scale of 30 pixels = 1 meter

Entity::Entity():
    m_body(nullptr)
{

}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
}

void Entity::update()
{

}

void Entity::setPosition(float x, float y)
{
    sf::Transformable::setPosition(x,y);
    m_body->SetTransform(b2Vec2(x/SCALE, y/SCALE), m_body->GetAngle());
}

// TODO set rotation
