#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <sstream>
#include <string>
#include <memory>

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include "MyContactListener.h"
#include "Entity.h"
#include "Hero.h"

class Game
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

        sf::RectangleShape m_groundShape;
        b2Body* m_groundBody;

        sf::Text m_statisticsText;
        sf::Font m_font;
        sf::Time m_statisticsUpdateTime;
		std::size_t	m_statisticsNumFrames;
};

#endif // GAME_H
