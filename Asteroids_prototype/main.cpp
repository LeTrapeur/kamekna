#include <SFML/graphics.hpp>
#include<iostream>
#include<vector>

int Orientation(const sf::Vector2f& p1, const sf::Vector2f& p2, const sf::Vector2f& p)
{
    // Determinant
    int Orin = (p2.x - p1.x) * (p.y - p1.y) - (p.x - p1.x) * (p2.y - p1.y);

    if (Orin > 0)
        return -1; //          (* Orientaion is to the left-hand side  *)
    if (Orin < 0)
        return 1; // (* Orientaion is to the right-hand side *)

    return 0; //  (* Orientaion is neutral aka collinear  *)
}

sf::Vector2f getMostLeft(const std::vector< sf::Vector2f >& pts)
{
    sf::Vector2f ptLeft = pts.at(0);
    for(size_t i = 1; i < pts.size() ; i++)
        {
            if(pts.at(i).x < ptLeft.x)
                ptLeft = pts[i];
        }
    return ptLeft;
}

std::vector< sf::Vector2f > ConvexHull(const std::vector< sf::Vector2f >& points)
        {
            std::vector< sf::Vector2f > hull;

            // get leftmost point
            sf::Vector2f vPointOnHull = getMostLeft(points);
            sf::Vector2f vEndpoint;
            do
            {
                hull.push_back(vPointOnHull);
                vEndpoint = points.at(0);

                for (size_t i = 1; i < points.size(); i++)
                {
                    if ((vPointOnHull == vEndpoint)
                        || (Orientation(vPointOnHull, vEndpoint, points[i]) == -1))
                    {
                        vEndpoint = points[i];
                    }
                }

                vPointOnHull = vEndpoint;

            }
            while (vEndpoint != hull.at(0));

            return hull;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Asteroids prototype");

    std::vector< sf::Vector2f > randomPoints;
    randomPoints.push_back(sf::Vector2f(100,500));
    randomPoints.push_back(sf::Vector2f(120,375));
    randomPoints.push_back(sf::Vector2f(400,300));
    randomPoints.push_back(sf::Vector2f(50,500));
    randomPoints.push_back(sf::Vector2f(70,220));

    std::vector< sf::Vector2f > sortPoints;
    sortPoints = ConvexHull(randomPoints);

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

        for(size_t i=0; i<randomPoints.size(); i++)
        {
            sf::RectangleShape point(sf::Vector2f(5,5));
            point.setOrigin(2.5f,2.5f);
            point.setFillColor(sf::Color::Red);
            point.setPosition(randomPoints.at(i));

            window.draw(point);
        }

        sf::ConvexShape envelop(sortPoints.size());
        envelop.setFillColor(sf::Color(80, 170, 200, 200));
        for(size_t i=0; i< sortPoints.size(); i++)
        {
            for(size_t i=0; i< sortPoints.size(); i++)
            {
                envelop.setPoint(i, sortPoints[i]);
            }
            window.draw(envelop);
        }

        // Update the window
        window.display();
    }
    return EXIT_SUCCESS;
}
