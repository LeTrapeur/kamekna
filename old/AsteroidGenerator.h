#ifndef ASTEROIDGENERATOR_H
#define ASTEROIDGENERATOR_H

#include <SFML/Graphics.hpp>
#include <vector>

class Asteroid;

namespace AsteroidGenerator
{
    void                        makeRandomAsteroid(Asteroid& asteroid);

    std::vector<sf::Vector2f>   getRandomPoints(int nbPoints);
}

#endif // ASTEROIDGENERATOR_H
