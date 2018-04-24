//
// Created by tklempka on 24/04/18.
//

#ifndef FRK2D_PROJECT_TILEDMAPNODE_HPP
#define FRK2D_PROJECT_TILEDMAPNODE_HPP


#include <FRK2D/SceneNode.hpp>
#include <tmx/MapLoader.hpp>


class TiledMapNode : public SceneNode
{
public:
    explicit            TiledMapNode();

private:
    virtual void        drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    tmx::MapLoader       m_ml;
};


#endif //FRK2D_PROJECT_TILEDMAPNODE_HPP
