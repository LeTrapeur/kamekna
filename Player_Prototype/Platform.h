#ifndef PLATFORM_H
#define PLATFORM_H

#include "Entity.h"

class Platform : public Entity
{
    public:
        Platform(b2World& world);

        virtual void update();
    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    private:
        sf::RectangleShape m_shape;
};

#endif // PLATFORM_H
