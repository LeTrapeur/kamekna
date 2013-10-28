#include "Platform.h"

const float SCALE = 30.f; // Box2D works in a scale of 30 pixels = 1 meter

Platform::Platform(b2World& world): Entity(world, Entity::Type::Platform)
{
    const int FLOOR_WIDTH = 1024;
    const int FLOOR_HEIGHT = 32;

    setOrigin(sf::Vector2f(FLOOR_WIDTH/2,FLOOR_HEIGHT/2));
    m_shape.setSize(sf::Vector2f(FLOOR_WIDTH,FLOOR_HEIGHT));
    m_shape.setFillColor(sf::Color::Black);
}

void Platform::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    //states.transform *= getTransform();
    target.draw(m_shape, states);
}
