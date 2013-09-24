#include <iostream>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

const float SCALE = 30.f; // SFML => BOX2D We have to divide by SCALE and multiply it the other way round


int main()
{
    // Graphic window
    const int WINDOW_LENGTH = 1024;
    const int WINDOW_WIDTH = 768;
    sf::RenderWindow window(sf::VideoMode(WINDOW_LENGTH, WINDOW_WIDTH), "Prototype player");
    window.setFramerateLimit(60);

    // Physical world
    const float WORLD_GRAVITY = 9.8f;
    b2World world(b2Vec2(0, WORLD_GRAVITY));

    //Floor
    const int FLOOR_LENGTH = 1024;
    const int FLOOR_WIDTH = 32;

    sf::RectangleShape floor;
    floor.setSize(sf::Vector2f(FLOOR_LENGTH,FLOOR_WIDTH));
    floor.setOrigin(sf::Vector2f(FLOOR_LENGTH/2,FLOOR_WIDTH/2));
    floor.setFillColor(sf::Color::Black);
    floor.setPosition(WINDOW_LENGTH/2,WINDOW_WIDTH-(FLOOR_WIDTH/2));// Center

    b2BodyDef GroundBodyDef;
    GroundBodyDef.position = b2Vec2(floor.getPosition().x/SCALE, floor.getPosition().y/SCALE);
    GroundBodyDef.type = b2_staticBody;
    b2Body* groundBody = world.CreateBody(&GroundBodyDef);

    b2FixtureDef GroundFixtureDef;
    b2PolygonShape GroundShape;
    GroundShape.SetAsBox((FLOOR_LENGTH/2.0f)/SCALE, (FLOOR_WIDTH/2.0f)/SCALE);
    GroundFixtureDef.shape = &GroundShape;
    GroundFixtureDef.density = 1.0f;
    groundBody->CreateFixture(&GroundFixtureDef);

    // Player
    const int PLAYER_LENGTH = 32;
    const int PLAYER_WIDTH = 64;

    sf::RectangleShape player;
    player.setSize(sf::Vector2f(PLAYER_LENGTH,PLAYER_WIDTH));
    player.setOrigin(sf::Vector2f(PLAYER_LENGTH/2,PLAYER_WIDTH/2));
    player.setFillColor(sf::Color::Red);
    player.setPosition(WINDOW_LENGTH/2,WINDOW_WIDTH/2);// Center

    b2BodyDef PlayerBodyDef;
    PlayerBodyDef.type = b2_dynamicBody;
    PlayerBodyDef.position = b2Vec2(player.getPosition().x/SCALE, player.getPosition().y/SCALE);
    PlayerBodyDef.fixedRotation = true;
    b2Body* playerBody = world.CreateBody(&PlayerBodyDef);

    b2FixtureDef PlayerFixtureDef;
    b2PolygonShape PlayerShape;
    PlayerShape.SetAsBox((PLAYER_LENGTH/2.0f)/SCALE, (PLAYER_WIDTH/2.0f)/SCALE);
    PlayerFixtureDef.shape = &PlayerShape;
    PlayerFixtureDef.density = 1.0f;
    playerBody->CreateFixture(&PlayerFixtureDef);

    // Game loop
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        world.Step(1.0f/60.0f, 8, 4);

        floor.setPosition(groundBody->GetPosition().x * SCALE, groundBody->GetPosition().y * SCALE);
        player.setPosition(playerBody->GetPosition().x * SCALE, playerBody->GetPosition().y * SCALE);

        window.clear(sf::Color::White);

        window.draw(floor);
        window.draw(player);

        window.display();
    }

    return 0;
}
