#ifndef ASTEROID_H
#define ASTEROID_H

#include <vector>
#include <SFML/graphics.hpp>

#include "AsteroidGenerator.h"

class Asteroid : public sf::Transformable, public sf::Drawable, private sf::NonCopyable
{
    public:
        Asteroid();
        friend void AsteroidGenerator::makeRandomAsteroid(Asteroid& asteroid);

    private:
        virtual void draw (sf::RenderTarget& target, sf::RenderStates states) const;

    private:
        sf::ConvexShape shape;
};



#endif // ASTEROID_H
