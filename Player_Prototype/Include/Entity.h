#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include "DataTables.h"

class Entity : public sf::Transformable, public sf::Drawable, private sf::NonCopyable
{
    public:
        enum Type
        {
            Hero,
            Platform,
            TypeCount,
        };
    public:
        explicit Entity(b2World& world, Entity::Type type);
        virtual void update();

        void setPosition(float x, float y);
        void setRotation(float angle);

    protected:
        b2Body* m_body;

    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};

constexpr float pi() { return std::atan(1)*4; }

#endif // ENTITY_H
