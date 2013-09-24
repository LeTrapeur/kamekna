#include <iostream>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

const float SCALE = 30.f;

int main()
{
    // Graphic window
    const int WINDOW_LENGTH = 1024;
    const int WINDOW_WIDTH = 768;
    sf::RenderWindow window(sf::VideoMode(WINDOW_LENGTH, WINDOW_WIDTH), "Prototype player");
    // Physical world
    const int WORLD_GRAVITY = 9.8;
    b2World world(b2Vec2(0, -WORLD_GRAVITY));
    // Floor
    const int FLOOR_LENGTH = 1024;
    const int FLOOR_WIDTH = 32;

    sf::RectangleShape floor;
    floor.setSize(sf::Vector2f(FLOOR_LENGTH,FLOOR_WIDTH));
    floor.setOrigin(sf::Vector2f(FLOOR_LENGTH/2,FLOOR_WIDTH/2));
    floor.setFillColor(sf::Color::Black);
    floor.setPosition(WINDOW_LENGTH/2,WINDOW_WIDTH-(FLOOR_WIDTH/2));// Center

    b2BodyDef BodyDef;
    BodyDef.position = b2Vec2((WINDOW_LENGTH/2.0f)/SCALE, (WINDOW_WIDTH-(FLOOR_WIDTH/2.0f))/SCALE);
    BodyDef.type = b2_staticBody;
    b2Body* groundBody = world.CreateBody(&BodyDef);

    b2FixtureDef FixtureDef;
    b2PolygonShape Shape;
    Shape.SetAsBox((FLOOR_LENGTH/2.0f)/SCALE, (FLOOR_WIDTH/2.0f)/SCALE);
    FixtureDef.shape = &Shape;
    groundBody->CreateFixture(&FixtureDef);


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        world.Step(1/60, 8, 4);

        floor.setPosition(groundBody->GetPosition().x * SCALE, groundBody->GetPosition().y * SCALE);

        window.clear(sf::Color::White);

        window.draw(floor);

        window.display();
    }

    return 0;
}
