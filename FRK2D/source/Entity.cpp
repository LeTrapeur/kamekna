#include <FRK2D/Entity.hpp>

#include <FRK2D/Utility.hpp>

//TODO PhysicalEntity instead ?

const float SCALE = 30.f; // Box2D works in a scale of 30 pixels = 1 meter

Entity::Entity(b2Body* body):
    m_body(body),
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
        setPosition(m_body->GetWorldCenter().x * SCALE, m_body->GetWorldCenter().y * SCALE);
        setRotation(m_body->GetAngle() * Utility::pi()/180);
    }
}

void Entity::setPosition(float x, float y)
{
    Entity::setPosition(sf::Vector2f(x, y));
}

void Entity::setPosition(const sf::Vector2f& pos)
{
    sf::Transformable::setPosition(pos);
    m_body->SetTransform(b2Vec2(getWorldPosition().x / SCALE, getWorldPosition().y / SCALE), m_body->GetAngle());
}

void Entity::setRotation(float angle)
{
    this->rotate(angle);
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

void Entity::setGravityActivated(bool activated)
{
    if(activated)
        m_body->SetGravityScale(1.f);
    else
        m_body->SetGravityScale(0.f);
}
bool Entity::getGravityActivated()
{
    return m_body->GetGravityScale() != 0;
}

void Entity::destroy()
{
    m_isDestroyed = true;
}

bool Entity::isDestroyed() const
{
    return m_isDestroyed;
}
