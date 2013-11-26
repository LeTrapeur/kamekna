#ifndef SCENENODE_H
#define SCENENODE_H

#include<memory>
#include <algorithm>
#include<vector>
#include<assert.h>

#include <SFML/Graphics.hpp>

#include "Command.h"
#include "Category.h"

class SceneNode : public sf::Transformable, public sf::Drawable, private sf::NonCopyable
{
    public:
        typedef std::unique_ptr<SceneNode> Ptr;

    public:
        explicit                    SceneNode();

        void                        attachChild(Ptr child);
        Ptr                         detachChild(const SceneNode& node);

        void                        update(sf::Time dt);

        virtual unsigned int        getCategory() const;
        void                        onCommand(const Command& command, sf::Time dt);

    private:
        virtual void                draw(sf::RenderTarget& target, sf::RenderStates states) const final;
        virtual void                drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

        virtual void                updateCurrent(sf::Time dt);
        void                        updateChildren(sf::Time dt);

    private:
        std::vector<Ptr>            m_children;
        SceneNode*                  m_parent;
};

#endif // SCENENODE_H
