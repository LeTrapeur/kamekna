#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <sstream>
#include <string>
#include <memory>
#include <list>

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include "MyContactListener.h"
#include "Entity.h"
#include "Hero.h"
#include "Platform.h"

class Game : private sf::NonCopyable
{
    public:
        Game();
        void run();

    private:
        void processEvents();
        void processInputs();
        void update(sf::Time elapsedTime);
        void updateStatistics(sf::Time elapsedTime);
        void render();

    private:
        sf::RenderWindow m_window;
        sf::View m_gameView;
        sf::View m_miniMapView;

        b2World m_world;
        MyContactListener m_contactListener;

        std::unique_ptr<Hero> ladral;
        std::unique_ptr<Platform> platform;
        //ListEntities m_entities;

        sf::Text m_statisticsText;
        sf::Font m_font;
        sf::Time m_statisticsUpdateTime;
		std::size_t	m_statisticsNumFrames;
};

#endif // GAME_H
