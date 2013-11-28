#ifndef ASTRONAUT_H
#define ASTRONAUT_H

#include "Being.h"

class Astronaut : public Being
{
    public:
                                Astronaut(Type type, const TextureHolder& textures, const FontHolder& fonts, b2World& world);

        void                    thrusterUp();
        void                    thrusterDown();
        void                    thrusterLeft();
        void                    thrusterRight();

    private:

};

#endif // ASTRONAUT_H
