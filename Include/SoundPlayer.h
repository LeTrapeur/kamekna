#ifndef SOUNDPLAYER_H
#define SOUNDPLAYER_H

#include <list>

#include <SFML/Audio.hpp>

#include "ResourceHolder.h"

class SoundPlayer : private sf::NonCopyable
{
    public:
                                SoundPlayer();

        void                    play(SoundEffect::ID effect);
        void                    removeStoppedSounds();
    private:
        SoundBufferHolder       m_soundBuffers;
        std::list<sf::Sound>    m_sounds;
};

#endif // SOUNDPLAYER_H
