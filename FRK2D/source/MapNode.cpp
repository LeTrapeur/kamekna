//
// Created by tklempka on 24/04/18.
//

#include <memory> #include <tmx/MapLoader.hpp>
#include <tmx/tmx2box2d.hpp>
#include <tmx/DebugShape.hpp>

#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include <Box2D/Collision/Shapes/b2CircleShape.h>

#include "FRK2D/MapNode.hpp"

MapNode::MapNode(TiledMapHolder& maps, b2World& world, bool debug):
    m_maps(maps),
    m_map(m_maps.get(TiledMaps::Default).getMap()),
    m_debug(debug)
{
    auto& layers = m_map->getLayers();
    tmx::BodyCreator bodyCreator;
    for (auto& l : layers)
    {
        if (l.name == "static") //static bodies which make up the map geometry
        {
            for (auto& o : l.objects)
            {

                b2Body* b = bodyCreator.add(o, world);
                //b->SetTransform(b2Vec2(tmx::sfToBoxVec(o.getPosition())), 0.f);

                if(m_debug)
                {
                    //iterate over body info to create some visual debugging shapes to help visualise
                    m_debugBoxes.push_back(std::make_unique<sf::RectangleShape>(sf::Vector2f(6.f, 6.f)));
                    sf::Vector2f pos = tmx::boxToSfVec(b->GetPosition());
                    m_debugBoxes.back()->setPosition(pos);
                    m_debugBoxes.back()->setOrigin(3.f, 3.f);

                    for (b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext()) {
                        b2Shape::Type shapeType = f->GetType();
                        if (shapeType == b2Shape::e_polygon) {
                            DebugShape ds;
                            ds.setPosition(pos);
                            auto *ps = (b2PolygonShape *) f->GetShape();

                            int count = ps->GetVertexCount();
                            for (int i = 0; i < count; i++)
                                ds.addVertex(sf::Vertex(tmx::boxToSfVec(ps->GetVertex(i)), sf::Color::Green));

                            ds.addVertex(sf::Vertex(tmx::boxToSfVec(ps->GetVertex(0)), sf::Color::Green));
                            m_debugShapes.push_back(ds);
                        }
                    }
                }
                //std::cout << tmx::boxToSfVec(body->GetPosition()).x << " " << tmx::boxToSfVec(body->GetPosition()).y << std::endl;
                //std::cout << tmx::boxToSfVec(body->GetPosition()).x << " " << tmx::boxToSfVec(body->GetPosition()).y << std::endl;
                //std::cout << o.getName() << " at : " << o.getPosition().x << " " << o.getPosition().y << " size: " << o.getAABB().width << " " << o.getAABB().height << std::endl;
                //std::unique_ptr<Platform> platform(new Platform(o.GetAABB().width, o.GetAABB().height, tmx::BodyCreator::Add(o, m_physicWorld)));
                //platform->setPosition(o.GetCentre().x, o.GetCentre().y); // TODO trouver origine
                //m_sceneLayers[Space]->attachChild(std::move(platform));
            }
        }
    }

}


void MapNode::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const {

    target.draw(*m_map, states);
    if(m_debug)
    {
        for (const auto& s : m_debugShapes)
            target.draw(s);

        for (const auto& s : m_debugBoxes)
            target.draw(*s);
    }
}

unsigned int MapNode::getCategory() const
{
    return Category::LowerScene;
}

