#include <SFML/graphics.hpp>
#include <iostream>
#include <vector>

#include "Asteroid.h"
#include "Utility.h"


int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Asteroids prototype");
    Asteroid asteroid;
    AsteroidGenerator::makeRandomAsteroid(&asteroid);

    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed)
                window.close();
        }
        // Clear screen
        window.clear(sf::Color::White);

        window.draw(asteroid);

        // Update the window
        window.display();
    }
    return EXIT_SUCCESS;
}
