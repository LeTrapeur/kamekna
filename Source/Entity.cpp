#include "Entity.h"

#include "Utility.h"

const float SCALE = 30.f; // Box2D works in a scale of 30 pixels = 1 meter

Entity::Entity():
    m_body(nullptr),
    m_isDestroyed(false)
{}

Entity::~Entity()
{
    m_body->GetWorld()->DestroyBody(m_body); // Delete the body in its world
}

b2Body* Entity::getBody() const
{
    return m_body;
}

void Entity::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
}

void Entity::updateCurrent(sf::Time dt, CommandQueue& commands)
{
    if(m_body->GetType() == b2_dynamicBody)
    {
        setPosition(m_body->GetPosition().x * SCALE, m_body->GetPosition().y * SCALE);
        setRotation(m_body->GetAngle()*Utility::pi()/180);
    }
}

unsigned int Entity::getCategory() const
{
    return Category::LowerScene;
}

void Entity::setPosition(float x, float y)
{
    sf::Transformable::setPosition(x,y);
    m_body->SetTransform(b2Vec2(x/SCALE, y/SCALE), m_body->GetAngle());
}

void Entity::setPosition(const sf::Vector2f& pos)
{
    sf::Transformable::setPosition(pos);
    m_body->SetTransform(b2Vec2(pos.x/SCALE, pos.y/SCALE), m_body->GetAngle());
}

void Entity::setRotation(float angle)
{
    sf::Transformable::setRotation(angle);
    m_body->SetTransform(b2Vec2(sf::Transformable::getPosition().x/SCALE, sf::Transformable::getPosition().y/SCALE), (angle*Utility::pi())/180);
}

void Entity::resetForces()
{
    m_body->SetAngularVelocity(0);
    m_body->SetLinearVelocity(b2Vec2(0.f,0.f));
}

float Entity::getTotalVelocity() const
{
    return (std::sqrt(std::pow(m_body->GetLinearVelocity().x,2)+std::pow(m_body->GetLinearVelocity().y,2))) * SCALE;
}

// TODO on n peut pas supprimer un body pendant un step ou un callback

void Entity::destroy()
{
    m_isDestroyed = true;
}

bool Entity::isDestroyed() const
{
    return m_isDestroyed;
}
