#include "Asteroid.h"

Asteroid::Asteroid()
{

    textureAsteroid.loadFromFile("textureAsteroid.png");
    shape.setTexture(&textureAsteroid);
}

void Asteroid::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(shape, states);
    for(size_t i = 0; i < shape.getPointCount(); i++)
    {
        sf::RectangleShape point(sf::Vector2f(5.f, 5.f));
        point.setFillColor(sf::Color::Red);
        point.setOrigin(shape.getOrigin().x + 2.5f, shape.getOrigin().y + 2.5f);
        point.setPosition(shape.getPoint(i));
        target.draw(point, states);
    }
}
