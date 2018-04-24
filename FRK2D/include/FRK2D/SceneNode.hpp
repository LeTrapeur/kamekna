#ifndef SCENENODE_H
#define SCENENODE_H

#include<memory>
#include <algorithm>
#include <vector>
#include <assert.h>

#include <SFML/Graphics.hpp>

#include <FRK2D/Command.hpp>
#include <FRK2D/Category.hpp>
#include <FRK2D/SoundPlayer.hpp>
#include <FRK2D/CommandQueue.hpp>

class SceneNode : public sf::Transformable, public sf::Drawable, private sf::NonCopyable
{
    public:
        typedef std::unique_ptr<SceneNode> Ptr;

    public:
        explicit                    SceneNode(Category::Type category = Category::None);

        void                        attachChild(Ptr child);
        Ptr                         detachChild(const SceneNode& node);

        void                        update(sf::Time dt, CommandQueue& commands);

        virtual unsigned int        getCategory() const;
        void                        onCommand(const Command& command, sf::Time dt);
        void                        playLocalSound(CommandQueue& commands, SoundEffect::ID effect);

        sf::Vector2f                getWorldPosition() const;
        sf::Transform               getWorldTransform() const;

        void                        removeWrecks();

        virtual bool                isMarkedForRemoval() const;
        virtual bool                isDestroyed() const;

    private:
        virtual void                draw(sf::RenderTarget& target, sf::RenderStates states) const final;
        virtual void                drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

        virtual void                updateCurrent(sf::Time dt, CommandQueue& commands);
        void                        updateChildren(sf::Time dt, CommandQueue& commands);

    private:
        std::vector<Ptr>            m_children;
        SceneNode*                  m_parent;

        Category::Type              m_defaultCategory;
};

#endif // SCENENODE_H
