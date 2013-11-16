#ifndef WORLD_H
#define WORLD_H

#include <iostream>
#include <sstream>
#include <string>
#include <memory>
#include <array>
#include <list>

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include "MyContactListener.h"
#include "ResourceHolder.h"
#include "SceneNode.h"
#include "SpriteNode.h"
#include "Entity.h"
#include "Being.h"
#include "Platform.h"
#include "Asteroid.h"

class World
{
    private:
        enum Layer
        {
            Background,
            Space,
            LayerCount
        };
    public:
        explicit World(sf::RenderWindow& window);

        void update(sf::Time dt);
        void draw();

        // Has to be changed with the commands system
        Being* getPtrPlayer();

    private:
        void loadTextures();
        void buildScene();

    private:
        sf::RenderWindow& m_window;
        sf::View m_worldView;
        sf::View m_minimapView;

        TextureHolder m_textures;

        b2World m_physicWorld;
        MyContactListener m_contactListener;
        sf::FloatRect m_worldBounds;

        SceneNode m_sceneGraph;
        std::array<SceneNode*, LayerCount> m_sceneLayers;
        // To be improved
        Being* m_player;
        sf::Vector2f m_spawnPosition;

};

#endif // WORLD_H
