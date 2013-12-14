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

    void centerOrigin(sf::Sprite& sprite);

    void centerOrigin(sf::Text& text);

    float length(sf::Vector2f vector);

    sf::Vector2f unitVector(sf::Vector2f vector);
}

#endif // UTILITY_H
