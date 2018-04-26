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
    explicit            MapNode(tmx::MapLoader& map, b2World& world, bool debug = false);

    void                loadMap(TiledMaps::ID map);


private:
    virtual void        drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    tmx::MapLoader&                         m_map; // We have to keep a reference on this one because drawing layer one by one is not possible (internal culling with views)
    tmx::MapLayer                           m_sceneryLayer;
    tmx::MapLayer                           m_staticGeometryLayer;

    bool                                    m_debug;
    std::vector<std::unique_ptr<sf::Shape>> m_debugBoxes;
    std::vector<DebugShape>                 m_debugShapes;

    unsigned int                            getCategory() const;
};

#endif //FRK2D_PROJECT_TILEDMAPNODE_HPP
