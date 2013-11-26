#ifndef APPLICATION_H
#define APPLICATION_H

#include <iostream>
#include <sstream>

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

#include "ResourceHolder.h"
#include "Player.h"
#include "StateStack.h"
#include "State.h"

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
        Player              m_player;
        TextureHolder       m_textures;
	  	FontHolder	        m_fonts;

		StateStack          m_stateStack;

        sf::Text            m_statisticsText;
        sf::Time            m_statisticsUpdateTime;
		std::size_t	        m_statisticsNumFrames;
};

#endif // APPLICATION_H
