#include <iostream>
#include <sstream>
#include <string>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

const float SCALE = 30.f; // Box2D works in a scale of 30 pixels = 1 meter
int numFootContacts = 0;

class MyContactListener : public b2ContactListener
  {
      void BeginContact(b2Contact* contact) {
          //check if fixture A was the foot sensor
          void* fixtureUserData = contact->GetFixtureA()->GetUserData();
          if ( (int)fixtureUserData == 3 )
          {
             numFootContacts++;
          }

          //check if fixture B was the foot sensor
          fixtureUserData = contact->GetFixtureB()->GetUserData();
          if ( (int)fixtureUserData == 3 )
          {
              numFootContacts++;
          }
      }

      void EndContact(b2Contact* contact) {
          //check if fixture A was the foot sensor
          void* fixtureUserData = contact->GetFixtureA()->GetUserData();
          if ( (int)fixtureUserData == 3 )
          {
                numFootContacts--;
          }
          //check if fixture B was the foot sensor
          fixtureUserData = contact->GetFixtureB()->GetUserData();
          if ( (int)fixtureUserData == 3 )
          {
                numFootContacts--;
          }
      }
  };

int main()
{
    // Graphic window
    const int WINDOW_WIDTH = 1280;
    const int WINDOW_HEIGHT = 720;
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Prototype player");
    sf::View game_view = window.getView();
    window.setView(game_view);
    window.setFramerateLimit(60);

    sf::View mini_map_view = window.getView();
    mini_map_view.zoom(4.0f);
    mini_map_view.setViewport(sf::FloatRect(0.85f, 0.f, 0.15f, 0.15f));

    // Physical world
    const float WORLD_GRAVITY = 15.0f;
    b2World world(b2Vec2(0, WORLD_GRAVITY));
    MyContactListener contact_listener;
    world.SetContactListener(&contact_listener);

    //Floor
    const int FLOOR_WIDTH = 1024;
    const int FLOOR_HEIGHT = 32;

    sf::RectangleShape floor;
    floor.setSize(sf::Vector2f(FLOOR_WIDTH,FLOOR_HEIGHT));
    floor.setOrigin(sf::Vector2f(FLOOR_WIDTH/2,FLOOR_HEIGHT/2));
    floor.setFillColor(sf::Color::Black);
    floor.setPosition(WINDOW_WIDTH/2,WINDOW_HEIGHT-(FLOOR_HEIGHT/2));// Center

    b2BodyDef GroundBodyDef;
    GroundBodyDef.position = b2Vec2(floor.getPosition().x/SCALE, floor.getPosition().y/SCALE);
    GroundBodyDef.type = b2_staticBody;
    b2Body* groundBody = world.CreateBody(&GroundBodyDef);

    b2FixtureDef GroundFixtureDef;
    b2PolygonShape GroundShape;
    GroundShape.SetAsBox((FLOOR_WIDTH/2.0f)/SCALE, (FLOOR_HEIGHT/2.0f)/SCALE);
    GroundFixtureDef.shape = &GroundShape;
    GroundFixtureDef.density = 1.0f;
    groundBody->CreateFixture(&GroundFixtureDef);

    // Player
    const int PLAYER_WIDTH = 32;
    const int PLAYER_HEIGHT = 64;

    sf::RectangleShape player;
    player.setSize(sf::Vector2f(PLAYER_WIDTH,PLAYER_HEIGHT));
    player.setOrigin(sf::Vector2f(PLAYER_WIDTH/2,PLAYER_HEIGHT/2));
    player.setFillColor(sf::Color::Red);
    player.setPosition(WINDOW_WIDTH/2,WINDOW_HEIGHT/2);// Center

    b2BodyDef PlayerBodyDef;
    PlayerBodyDef.type = b2_dynamicBody;
    PlayerBodyDef.position = b2Vec2(player.getPosition().x/SCALE, player.getPosition().y/SCALE);
    PlayerBodyDef.fixedRotation = true;
    b2Body* playerBody = world.CreateBody(&PlayerBodyDef);

    b2FixtureDef PlayerFixtureDef;
    b2PolygonShape PlayerShape;
    PlayerShape.SetAsBox((PLAYER_WIDTH/2.0f)/SCALE, (PLAYER_HEIGHT/2.0f)/SCALE);
    PlayerFixtureDef.shape = &PlayerShape;
    PlayerFixtureDef.density = 1.0f;
    PlayerFixtureDef.friction = 0.3f;
    playerBody->CreateFixture(&PlayerFixtureDef);

    //add foot sensor fixture
    PlayerShape.SetAsBox(((PLAYER_WIDTH-10)/2.0f)/SCALE, 5/SCALE, b2Vec2(0,(PLAYER_HEIGHT/2.0f)/SCALE), 0);
    PlayerFixtureDef.isSensor = true;
    b2Fixture* footSensorFixture = playerBody->CreateFixture(&PlayerFixtureDef);
    footSensorFixture->SetUserData( (void*)3 );

    // DEBUG Text
    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
    {
        std::cout << "Unable to load font..." << std::endl;
    }
    sf::Text text;
    text.setFont(font);
    text.setString("DEBUG");
    text.setCharacterSize(24);
    text.setColor(sf::Color::Blue);

    // Game loop
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::Resized)
            {}
            if (event.type == sf::Event::KeyPressed)
            {
                // Jumping
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
                {
                    if (numFootContacts >= 1)
                    playerBody->ApplyLinearImpulse(b2Vec2(0,-playerBody->GetMass()*8), playerBody->GetWorldCenter());
                }
            }
        }

        // Moving left/right
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
        {
            if (numFootContacts >= 1 && playerBody->GetLinearVelocity().x * SCALE > -150)
                playerBody->ApplyForce(b2Vec2(-playerBody->GetMass()*8,0), playerBody->GetWorldCenter());
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        {
            if (numFootContacts >= 1 && playerBody->GetLinearVelocity().x * SCALE < 150)
                playerBody->ApplyForce(b2Vec2(playerBody->GetMass()*8,0), playerBody->GetWorldCenter());
        }

        // Thrusters
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
        {
            playerBody->ApplyForce(b2Vec2(0, playerBody->GetMass()*25), playerBody->GetWorldCenter());
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
        {
            playerBody->ApplyForce(b2Vec2(0, -playerBody->GetMass()*25), playerBody->GetWorldCenter());
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        {
            playerBody->ApplyForce(b2Vec2(playerBody->GetMass()*10, 0), playerBody->GetWorldCenter());
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        {
            playerBody->ApplyForce(b2Vec2(-playerBody->GetMass()*10, 0), playerBody->GetWorldCenter());
        }
        // Update physic
        world.Step(1.0f/60.0f, 8, 4);

        // Aplly physic to objects
        floor.setPosition(groundBody->GetPosition().x * SCALE, groundBody->GetPosition().y * SCALE);
        player.setPosition(playerBody->GetPosition().x * SCALE, playerBody->GetPosition().y * SCALE);

        // DEBUG
        std::string str = static_cast<std::ostringstream*>(&(std::ostringstream() << "X: " << static_cast<int>(playerBody->GetPosition().x * SCALE) << " Y: " << static_cast<int>(playerBody->GetPosition().y * SCALE)
                                                         << "\nvX: " << static_cast<int>(playerBody->GetLinearVelocity().x * SCALE) << " vY: " << static_cast<int>(playerBody->GetLinearVelocity().y * SCALE)))
                                                         ->str();
        text.setString(str);

        // Display methods
        window.clear(sf::Color::White);
        game_view.setCenter(player.getPosition());
        window.setView(game_view);
        window.draw(floor);
        window.draw(player);
        text.setPosition(sf::Vector2f(window.mapPixelToCoords(sf::Vector2i(0,0))));
        window.draw(text);

        window.setView(mini_map_view);
        window.draw(floor);
        window.draw(player);

        window.display();
    }

    return 0;
}
