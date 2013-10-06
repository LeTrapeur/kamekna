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
        explicit World();

        void update(sf::Time dt);
        void draw();

    private:
        void loadTextures();
        void buildScene();

    private:
        sf::RenderWindow& m_window;
        sf::View m_worldView;

        ListEntities m_entities;

        Hero* m_player;

};

#endif // WORLD_H
