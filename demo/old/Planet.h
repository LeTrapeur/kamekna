#ifndef PLANET_H
#define PLANET_H

#include <vector>
#include <SFML/Graphics.hpp>

#include "Entity.h"
#include "ResourceHolder.h"

class Planet : public Entity
{
    public:
        explicit                Planet(const TextureHolder& textures,b2World& world);
        virtual unsigned int    getCategory() const;

    private:
        virtual void            drawCurrent (sf::RenderTarget& target, sf::RenderStates states) const;

    private:
        sf::CircleShape         m_shapePlanet;
        sf::CircleShape         m_shapeInfluence;

};

#endif // PLANET_H
