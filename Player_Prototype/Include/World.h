#ifndef WORLD_H
#define WORLD_H

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

class World
{
    public:
        typedef std::list<std::unique_ptr<Entity> > ListEntities;
    public:
        explicit World(sf::RenderWindow& window);

        void update(sf::Time dt);
        void draw();

        // Has to be changed with the commands system
        Hero* getPtrPlayer();

    private:
        void loadTextures();
        void buildScene();

    private:
        sf::RenderWindow& m_window;
        sf::View m_worldView;
        sf::View m_minimapView;

        b2World m_physicWorld;
        MyContactListener m_contactListener;

        ListEntities m_entities;
        // To be improved
        Hero* m_player;

};

#endif // WORLD_H
