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

#include "MyContactListener.hpp"
#include <FRK2D/ResourceHolder.hpp>
#include <FRK2D/CommandQueue.hpp>
#include <FRK2D/SceneNode.hpp>
#include <FRK2D/SoundPlayer.hpp>
#include <FRK2D/IA.hpp>
#include <Actor.hpp>


class World
{
    private:
        enum Layer
        {
            Background,
            Foreground,
            LayerCount
        };
    public:
        explicit                                World(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts, SoundPlayer& sounds, TiledMapHolder& maps);

        void                                    update(sf::Time dt);
        void                                    draw();

        CommandQueue&                           getCommandQueue();
        float                                   getPlayerLife() const;
        float                                   getPlayerPower() const;

        sf::Vector2f                            getMouseWorldPosition();


    private:
        void                                    loadTextures();
        void                                    buildScene();
        void                                    adaptPlayerPosition();
        void                                    adaptScrolling();
        void                                    updateSounds();

    private:
        sf::RenderWindow&                       m_window;
        sf::View                                m_worldView;
        sf::View                                m_minimapView;

        TextureHolder&                          m_textures;
        FontHolder&                             m_fonts;
        SoundPlayer&                            m_sounds;
        TiledMapHolder&                         m_maps;

        b2World                                 m_physicWorld;
        MyContactListener                       m_contactListener;
        sf::FloatRect                           m_worldBounds;

        SceneNode                               m_sceneGraph;
        std::array<SceneNode*, LayerCount>      m_sceneLayers;

        Actor*                                  m_player;
        //TODO généraliser spawning pour toutes les entités
        sf::Vector2f                            m_spawnPosition;

        CommandQueue                            m_commandQueue;

        //IA                                      m_ia;

};

#endif // WORLD_H
