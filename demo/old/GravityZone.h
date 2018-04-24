#ifndef GRAVITYZONE_H
#define GRAVITYZONE_H

#include "Entity.h"
#include "Category.h"


class GravityZone : public Entity
{
    public:
        explicit                GravityZone(int width, int height, b2Body* body);
        void                    addActorInside();
        void                    removeActorInside();
        bool                    hasPlayerInside();
        void                    setActivated(bool activated);
        bool                    getActivated();

        virtual unsigned int    getCategory() const;

    private:
        virtual void            updateCurrent(sf::Time dt, CommandQueue& commands);
        virtual void            drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

    private:
        sf::RectangleShape      m_shape;
        int                     m_actorsInside;
        bool                    m_isActivated;
};

#endif // GRAVITYZONE_H
