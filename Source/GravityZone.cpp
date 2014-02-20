#include "GravityZone.h"

// TODO Généraliser Zone ? Exemple zone de détction pour un système

GravityZone::GravityZone(int width, int height, b2Body* body):
    Entity(body),
    m_shape(sf::Vector2f(width, height)),
    m_actorsInside(0),
    m_isActivated(false)
{
    setOrigin(sf::Vector2f(width/2,height/2));

    m_body->GetFixtureList()->SetUserData(this);
    m_body->GetFixtureList()->SetSensor(true);

}

void GravityZone::setActivated(bool activated)
{
    m_isActivated = activated;
}
bool GravityZone::getActivated()
{
    return m_isActivated;
}

void GravityZone::addActorInside()
{
    m_actorsInside++;
}

void GravityZone::removeActorInside()
{
    m_actorsInside--;

    if(m_actorsInside < 0)
        m_actorsInside = 0;
}

bool GravityZone::hasPlayerInside()
{
    return m_actorsInside > 0;
}

void GravityZone::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_shape, states);
}

void GravityZone::updateCurrent(sf::Time dt, CommandQueue& commands)
{
    // TODO à remplacer avec activated une fois en place
    if(hasPlayerInside())
        m_shape.setFillColor(sf::Color(255, 0, 0, 100));
    else
        m_shape.setFillColor(sf::Color(0, 255, 0, 100));

    Entity::updateCurrent(dt,commands);
}

unsigned int GravityZone::getCategory() const
{
    return Category::GravityZone;
}
