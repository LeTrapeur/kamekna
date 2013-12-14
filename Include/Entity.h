#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include "SceneNode.h"

class Entity : public SceneNode
{
    public:
        explicit            Entity();

        void                setPosition(float x, float y);
        void                setPosition(const sf::Vector2f& pos);
        void                setRotation(float angle);
        void                resetForces();

        // une entité est immuablement représentée par un body dont on peut mesurer les caractèristiques publiquement ?
        b2Body*             m_body;

    protected:
        // b2body ?

    private:
        virtual void        drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

    protected:
        virtual void        updateCurrent(sf::Time dt, CommandQueue& commands);



};

constexpr float pi() { return std::atan(1)*4; }

#endif // ENTITY_H
