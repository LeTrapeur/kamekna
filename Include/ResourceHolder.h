#ifndef RESOURCEHOLDER_H
#define RESOURCEHOLDER_H

#include <map>
#include <string>
#include <memory>
#include <stdexcept>
#include <cassert>

namespace sf
{
    class Texture;
    class Font;
}

namespace Textures
{
    enum ID
    {
        SpaceBackground,
        Hero,
        Asteroid,
        TitleScreen,
    };
}

namespace Fonts
{
    enum ID
    {
        Main,
    };
}

template <typename Resource, typename Identifier>
class ResourceHolder
{
    public:
        void                                                load(Identifier id, const std::string& filename);

        template <typename Parameter>
        void                                                load(Identifier id, const std::string& filename, const Parameter& secondParam);

        Resource&                                           get(Identifier id);
        const Resource&                                     get(Identifier id) const;

    private:
        void                                                insertResource(Identifier id, std::unique_ptr<Resource> resource);

    private:
        std::map<Identifier, std::unique_ptr<Resource>>     mResourceMap;
};

typedef ResourceHolder<sf::Texture, Textures::ID>           TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID>                 FontHolder;

#include "ResourceHolder.inl"
#endif // RESOURCEHOLDER_H
