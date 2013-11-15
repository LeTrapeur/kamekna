#ifndef UTILITY_H
#define UTILITY_H

#include <SFML/graphics.hpp>
#include <vector>
#include <random>
#include <ctime>

namespace Utility
{
    int Orientation(const sf::Vector2f& p1, const sf::Vector2f& p2, const sf::Vector2f& p);

    sf::Vector2f getMostLeft(const std::vector< sf::Vector2f >& pts);

    std::vector< sf::Vector2f > ConvexHull(const std::vector< sf::Vector2f >& points);

    float randomFloatGenerator(float a, float b);
}

#endif // UTILITY_H
