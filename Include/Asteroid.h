#ifndef ASTEROID_H
#define ASTEROID_H

#include <vector>
#include <SFML/graphics.hpp>

#include "Entity.h"
#include "ResourceHolder.h"
#include "AsteroidGenerator.h"

class Asteroid : public Entity
{
    public:
        explicit        Asteroid(const TextureHolder& textures,b2World& world);
        friend void     AsteroidGenerator::makeRandomAsteroid(Asteroid& asteroid);

    private:
        virtual void    drawCurrent (sf::RenderTarget& target, sf::RenderStates states) const;

    private:
        sf::ConvexShape m_shape;
};



#endif // ASTEROID_H
