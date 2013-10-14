#ifndef UTILITY_H
#define UTILITY_H

#include <SFML/graphics.hpp>
#include <iostream>
#include <vector>


class Asteroid;

namespace AsteroidGenerator
{
    void makeRandomAsteroid(Asteroid& asteroid);

    std::vector<sf::Vector2f> getRandomPoints(int nbPoints);
}

namespace Utility
{
    int Orientation(const sf::Vector2f& p1, const sf::Vector2f& p2, const sf::Vector2f& p);

    sf::Vector2f getMostLeft(const std::vector< sf::Vector2f >& pts);

    std::vector< sf::Vector2f > ConvexHull(const std::vector< sf::Vector2f >& points);

    float randomFloatGenerator(float a, float b);
}

#endif // UTILITY_H
