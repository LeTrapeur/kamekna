//
// Created by tklempka on 25/04/18.
//

#ifndef FRK2D_PROJECT_TILEDMAP_HPP
#define FRK2D_PROJECT_TILEDMAP_HPP

#include <string>
#include <tmx/MapLoader.hpp>

class TiledMap
{
public:
    explicit                        TiledMap();
                                    ~TiledMap();

    bool                            loadFromFile(const std::string& filename);
    bool                            saveToFile(); //TODO
    tmx::MapLoader*                 getMap() const ;

private:
    std::unique_ptr<tmx::MapLoader> m_mapLoader;
    std::string                     m_filename;
};

#endif //FRK2D_PROJECT_TILEDMAP_HPP
