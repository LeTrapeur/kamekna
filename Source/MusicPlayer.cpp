#include "MusicPlayer.h"

#include <stdexcept>
#include <cassert>

MusicPlayer::MusicPlayer():
    m_music(),
    m_filenames(),
    m_volume(100.f)
{
    m_filenames[Music::MenuTheme] = "menutheme.ogg";
    m_filenames[Music::GameTheme] = "gametheme.ogg";
}

void MusicPlayer::play(Music::ID theme)
{
    std::string filename = m_filenames[theme];

    if(!m_music.openFromFile(filename))
        throw std::runtime_error("Music " + filename + " could not be loaded.");

    m_music.setVolume(m_volume);
    m_music.setLoop(true);
    m_music.play();
}

void MusicPlayer::stop()
{
    m_music.stop();
}

void MusicPlayer::setPaused(bool paused)
{
    if(paused)
        m_music.pause();
    else
        m_music.play();
}

void MusicPlayer::setVolume(float volume)
{
    assert(volume > 0);
    m_volume = volume;
}
