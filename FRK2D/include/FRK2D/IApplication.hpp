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

class IApplication
{
    public:
        IApplication();
        void                run();
        virtual             ~IApplication()= default;
        virtual void        registerStates()=0;
        virtual void        loadContent()=0;
        virtual void        loadSettings()=0;

    protected:
        void                processInputs();
        void                update(sf::Time elapsedTime);
        void                updateStatistics(sf::Time elapsedTime);
        void                render();

    protected:
        sf::RenderWindow    m_window;
		Player              m_player;

        SettingsHolder      m_settings;
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
