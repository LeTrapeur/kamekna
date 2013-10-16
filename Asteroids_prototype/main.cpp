#include <SFML/graphics.hpp>
#include <iostream>
#include <vector>

#include "Asteroid.h"
#include "Utility.h"


int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Asteroids prototype");
    Asteroid asteroid;
    AsteroidGenerator::makeRandomAsteroid(asteroid);

    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::R)
                {
                    // Refresh randomization
                    AsteroidGenerator::makeRandomAsteroid(asteroid);
                }
            }
        }
        // Clear screen
        window.clear(sf::Color::Black);

        window.draw(asteroid);

        // Update the window
        window.display();
    }
    return EXIT_SUCCESS;
}
