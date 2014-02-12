#ifndef PLATFORM_H
#define PLATFORM_H

#include "Entity.h"

class Platform : public Entity
{
    public:
        enum Type
        {
            Metal,
        };
    public:
        explicit                Platform(Type type, int width, int height, TextureHolder& textures, b2World& world);
        virtual unsigned int    getCategory() const;

    private:
        virtual void            drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
        static b2Body*          createBody(b2World& world);

    private:
        sf::RectangleShape      m_shape;
        Type                    m_type;
};

#endif // PLATFORM_H
