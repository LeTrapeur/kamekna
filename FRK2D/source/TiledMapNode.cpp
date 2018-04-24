//
// Created by tklempka on 24/04/18.
//

#include <tmx/MapLoader.hpp>
#include "FRK2D/TiledMapNode.hpp"

TiledMapNode::TiledMapNode() : m_ml("resources")
{
    m_ml.load("level.tmx");
}

void TiledMapNode::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const {

    target.draw(m_ml, states);
}
