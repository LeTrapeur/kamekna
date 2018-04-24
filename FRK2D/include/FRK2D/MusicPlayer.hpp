#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include <map>

#include <SFML/Audio.hpp>

namespace Music
{
    enum ID
    {
        MenuTheme,
        GameTheme,
    };
}

class MusicPlayer : private sf::NonCopyable
{
    public:
                    MusicPlayer();
        void        play(Music::ID theme);
        void        stop();
        void        setPaused(bool paused);
        void        setVolume(float volume);


    private:
        sf::Music                           m_music;
        std::map<Music::ID, std::string>    m_filenames;
        float                               m_volume;
};

#endif // MUSICPLAYER_H
