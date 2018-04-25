//
// Created by tklempka on 24/04/18.
//

#ifndef FRK2D_PROJECT_TILEDMAPNODE_HPP
#define FRK2D_PROJECT_TILEDMAPNODE_HPP


#include <FRK2D/SceneNode.hpp>
#include <tmx/MapLoader.hpp>

class MapNode : public SceneNode
{
public:
    explicit            MapNode(TiledMapHolder& maps, b2World& world, bool debug = false);

    void                loadMap(TiledMaps::ID map);


private:
    virtual void        drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    TiledMapHolder&                         m_maps;
    tmx::MapLoader*                         m_map;

    bool                                    m_debug;
    std::vector<std::unique_ptr<sf::Shape>> m_debugBoxes;
    std::vector<DebugShape>                 m_debugShapes;

    unsigned int getCategory() const;
};

#endif //FRK2D_PROJECT_TILEDMAPNODE_HPP
