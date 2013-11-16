#include "Utility.h"

namespace Utility
{
    float randomFloatGenerator(float a, float b)
    {
        static std::mt19937 e(time(NULL));
        static std::uniform_real_distribution<float> d(a, b);
        return d(e);
    }

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
}
