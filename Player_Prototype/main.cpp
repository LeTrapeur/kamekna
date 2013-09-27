#include <iostream>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

const float SCALE = 30.f; // Box2D works in a scale of 30 pixels = 1 meter


int main()
{
    // Graphic window
    const int WINDOW_LENGTH = 1024;
    const int WINDOW_WIDTH = 768;
    sf::RenderWindow window(sf::VideoMode(WINDOW_LENGTH, WINDOW_WIDTH), "Prototype player");
    sf::View view = window.getDefaultView();
    window.setView(view);
    window.setFramerateLimit(60);

    // Physical world
    const float WORLD_GRAVITY = 15.0f;
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
    PlayerFixtureDef.friction = 0.3f;
    playerBody->CreateFixture(&PlayerFixtureDef);

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
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Key::Add || event.key.code == sf::Keyboard::Key::P)
                {
                    view.zoom(0.8f);
                    window.setView(view);
                }
                if (event.key.code == sf::Keyboard::Key::Subtract || event.key.code == sf::Keyboard::Key::O)
                {
                    view.zoom(1.2f);
                    window.setView(view);
                }
            }
        }

        // Update physic
        world.Step(1.0f/60.0f, 8, 4);

        // Moving left/right
        // 703 matches the position of the floor, to be remplaced by a sensor
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
        {
            if (playerBody->GetPosition().y * SCALE > 703 && playerBody->GetLinearVelocity().x * SCALE > -150)
                playerBody->ApplyForce(b2Vec2(-playerBody->GetMass()*6,0), playerBody->GetWorldCenter());
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        {
            if (playerBody->GetPosition().y * SCALE > 703 && playerBody->GetLinearVelocity().x * SCALE < 150)
                playerBody->ApplyForce(b2Vec2(playerBody->GetMass()*6,0), playerBody->GetWorldCenter());
        }

        // Jumping
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
        {
            if (playerBody->GetPosition().y * SCALE > 703)
                playerBody->ApplyLinearImpulse(b2Vec2(0,-playerBody->GetMass()*8), playerBody->GetWorldCenter());
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

        // Aplly physic to objects
        floor.setPosition(groundBody->GetPosition().x * SCALE, groundBody->GetPosition().y * SCALE);
        player.setPosition(playerBody->GetPosition().x * SCALE, playerBody->GetPosition().y * SCALE);
        // DEBUG
        std::cout << "X: " << playerBody->GetLinearVelocity().x * SCALE << " Y: " << playerBody->GetLinearVelocity().y * SCALE << std::endl;

        // Display methods
        window.clear(sf::Color::White);
        window.draw(floor);
        window.draw(player);
        window.draw(text);
        window.display();
    }

    return 0;
}
