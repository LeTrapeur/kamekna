//
// Created by tklempka on 25/04/18.
//

#include <FRK2D/TiledMap.hpp>


TiledMap::TiledMap()
{}

TiledMap::~TiledMap()
{}

bool TiledMap::loadFromFile(const std::string &filename)
{
    m_filename = filename;
    auto pos = filename.rfind("/");
    if (pos!= std::string::npos) {
        m_mapLoader = std::make_unique<tmx::MapLoader>(filename.substr(0, pos)); // constrained by the lib. MapLoader has to have a root folder in the constructor
        return m_mapLoader->load(m_filename);
    }
    else
        return false;
}

tmx::MapLoader* TiledMap::getMap() const
{
    return  m_mapLoader.get();
}
