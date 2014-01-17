#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include "SceneNode.h"

class Entity : public SceneNode
{
    public:
        explicit                Entity();
        virtual unsigned int    getCategory() const;

        void                    setPosition(float x, float y);
        void                    setPosition(const sf::Vector2f& pos);
        void                    setRotation(float angle);
        void                    resetForces();
        float                   getTotalVelocity() const;

        // une entit� est immuablement repr�sent�e par un body dont on peut mesurer les caract�ristiques publiquement ?
        b2Body*                 m_body;

    protected:
        // TODO b2body ?

    private:
        virtual void            drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

    protected:
        virtual void            updateCurrent(sf::Time dt, CommandQueue& commands);
};

#endif // ENTITY_H
