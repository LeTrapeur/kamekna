#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include <FRK2D/SceneNode.hpp>

class Entity : public SceneNode
{
    public:
        explicit                Entity(b2Body* body);
                                ~Entity();

        void                    setPosition(float x, float y);
        void                    setPosition(const sf::Vector2f& pos);
        void                    setRotation(float angle);
        void                    resetForces();
        float                   getTotalVelocity() const;
        b2Body*                 getBody() const;

        void                    setGravityActivated(bool activated);
        bool                    getGravityAcvtivated();

        void                    destroy();
        virtual bool            isDestroyed() const;


        // TODO Warper pour passer body en private ?
    protected:
        b2Body*                 m_body;

    private:
        virtual void            drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
        bool                    m_isDestroyed;

    protected:
        virtual void            updateCurrent(sf::Time dt, CommandQueue& commands);
};

#endif // ENTITY_H
