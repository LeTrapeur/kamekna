#include "AsteroidGenerator.h"

#include "Utility.h"
#include "Asteroid.h"

namespace AsteroidGenerator
{
    std::vector<sf::Vector2f> getRandomPoints(int nbPoints)
    {
        std::vector<sf::Vector2f> data;
        for (size_t i = 0 ; i < nbPoints ; i++)
        {
            data.push_back(sf::Vector2f(Utility::randomFloatGenerator(100.f, 700.f),Utility::randomFloatGenerator(100.f, 400.f)));
        }
        return data;
    }

    void makeRandomAsteroid(Asteroid& asteroid)
    {
        std::vector< sf::Vector2f > randomPoints = getRandomPoints(10);
        std::vector< sf::Vector2f > sortPoints = Utility::ConvexHull(randomPoints);

        asteroid.shape.setPointCount(sortPoints.size());
        asteroid.shape.setOrigin(sortPoints.at(0));
        for(size_t i = 0; i < sortPoints.size(); i++)
        {
            asteroid.shape.setPoint(i, sortPoints.at(i));
        }
    }
}
