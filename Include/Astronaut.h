#ifndef ASTRONAUT_H
#define ASTRONAUT_H

#include "Being.h"

class TextNode;

class Astronaut : public Being
{
    public:
                                Astronaut(Type type, const TextureHolder& textures, const FontHolder& fonts, b2World& world);

        void                    thrusterUp();
        void                    thrusterDown();
        void                    thrusterLeft();
        void                    thrusterRight();

        float                   getPower() const;

    private:
        virtual void            updateCurrent(sf::Time dt);
        void                    checkThrusters();

    private:
        float                   m_power;
        bool                    m_isThrusting;
        sf::Clock               m_powerRecovery;
        sf::Time                m_powerRecoveryTime;
        TextNode*               m_powerDisplay;

};

#endif // ASTRONAUT_H
