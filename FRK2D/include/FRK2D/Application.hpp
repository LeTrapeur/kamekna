#ifndef APPLICATION_H
#define APPLICATION_H

#include <iostream>
#include <sstream>

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <FRK2D/SettingsParser.hpp>

#include <FRK2D/ResourceHolder.hpp>
#include <FRK2D/Player.hpp>
#include <FRK2D/MusicPlayer.hpp>
#include <FRK2D/SoundPlayer.hpp>
#include <FRK2D/StateStack.hpp>

class Application
{
    public:
        Application();
        void                run();
        void                registerStates();

    private:
        void                processInputs();
        void                update(sf::Time elapsedTime);
        void                updateStatistics(sf::Time elapsedTime);
        void                render();

    private:
        sf::RenderWindow    m_window;
        SettingsHolder      m_settings;
        Player              m_player;
        TextureHolder       m_textures;
	  	FontHolder	        m_fonts;
	  	MusicPlayer         m_music;
	  	SoundPlayer         m_sounds;

		StateStack          m_stateStack;

        sf::Text            m_statisticsText;
        sf::Time            m_statisticsUpdateTime;
		std::size_t	        m_statisticsNumFrames;
};

#endif // APPLICATION_H
