#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include "SceneNode.h"
#include "DataTables.h"

class Entity : public SceneNode
{
    public:
        explicit Entity(b2World& world);
        virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

        void setPosition(float x, float y);
        void setPosition(const sf::Vector2f& pos);
        void setRotation(float angle);

    protected:
        b2Body* m_body;

    private:
        virtual void updateCurrent(sf::Time dt);



};

constexpr float pi() { return std::atan(1)*4; }

#endif // ENTITY_H
