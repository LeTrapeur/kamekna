#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <sstream>
#include <string>

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

extern int numFootContacts;

class MyContactListener : public b2ContactListener
  {
      void BeginContact(b2Contact* contact) {
          void* fixtureUserData = contact->GetFixtureA()->GetUserData();
          if ( (int)fixtureUserData == 3 )
          {
             numFootContacts++;
          }
          fixtureUserData = contact->GetFixtureB()->GetUserData();
          if ( (int)fixtureUserData == 3 )
          {
              numFootContacts++;
          }
      }

      void EndContact(b2Contact* contact) {
          void* fixtureUserData = contact->GetFixtureA()->GetUserData();
          if ( (int)fixtureUserData == 3 )
          {
                numFootContacts--;
          }
          fixtureUserData = contact->GetFixtureB()->GetUserData();
          if ( (int)fixtureUserData == 3 )
          {
                numFootContacts--;
          }
      }
  };

class Game
{
    public:
        Game();
        void run();

    private:
        void processEvents();
        void update();
        void render();

    private:
        sf::RenderWindow m_window;
        b2World m_world;
        MyContactListener m_contactListener;


        sf::View m_gameView;
        sf::View m_miniMapView;

        sf::RectangleShape m_groundShape;
        b2Body* m_groundBody;

        sf::RectangleShape m_playerShape;
        b2Body* m_playerBody;

        sf::Text m_debugText;
        sf::Font m_font;

};

#endif // GAME_H
