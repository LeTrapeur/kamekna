#include "SceneNode.h"
#include "SoundNode.h"

SceneNode::SceneNode(Category::Type category):
    m_parent(nullptr),
    m_defaultCategory(category)
{
    //ctor
}

void SceneNode::attachChild(Ptr child)
{
    child->m_parent = this;
    m_children.push_back(std::move(child));
}

SceneNode::Ptr SceneNode::detachChild(const SceneNode& node)
{
    auto found = std::find_if(m_children.begin(), m_children.end(), [&] (Ptr& p) -> bool {return p.get() == &node; });
    assert(found != m_children.end());
    Ptr result = std::move(*found);
    result->m_parent = nullptr;
    m_children.erase(found);
    return result;
}

void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    drawCurrent(target, states);

    for(auto it = m_children.begin(); it != m_children.end(); ++it)
    {
        (*it)->draw(target, states);
    }
}
void SceneNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    // nothing here
}

void SceneNode::update(sf::Time dt, CommandQueue& commands)
{
    updateCurrent(dt, commands);
    updateChildren(dt, commands);
}

void SceneNode::updateCurrent(sf::Time dt, CommandQueue& commands)
{
     // nothing here
}

void SceneNode::updateChildren(sf::Time dt, CommandQueue& commands)
{
    for(auto it = m_children.begin(); it != m_children.end(); ++it)
    {
        (*it)->update(dt, commands);
    }
}

unsigned int SceneNode::getCategory() const
{
    return m_defaultCategory;
}

void SceneNode::onCommand(const Command& command, sf::Time dt)
{
    if(command.category & getCategory())
        command.action(*this, dt);

    for(auto it = m_children.begin(); it != m_children.end(); ++it)
        (*it)->onCommand(command, dt);
}

void SceneNode::playLocalSound(CommandQueue& commands, SoundEffect::ID effect)
{
    Command command;
    command.category = Category::SoundEffect;
    command.action = derivedAction<SoundNode>([effect](SoundNode& node, sf::Time dt)
                                              {
                                                  node.playSound(effect);
                                              });
    commands.push(command);
}

sf::Vector2f SceneNode::getWorldPosition() const
{
        return getWorldTransform() * sf::Vector2f();
}

sf::Transform SceneNode::getWorldTransform() const
{
        sf::Transform transform = sf::Transform::Identity;

        for (const SceneNode* node = this; node != nullptr; node = node->m_parent)
                transform = node->getTransform() * transform;

        return transform;
}

void SceneNode::removeWrecks()
{
        // Remove all children which request so
        auto wreckfieldBegin = std::remove_if(m_children.begin(), m_children.end(), std::mem_fn(&SceneNode::isMarkedForRemoval));
        m_children.erase(wreckfieldBegin, m_children.end());

        // Call function recursively for all remaining children
        std::for_each(m_children.begin(), m_children.end(), std::mem_fn(&SceneNode::removeWrecks));
}

bool SceneNode::isMarkedForRemoval() const
{
    return isDestroyed();
}
bool SceneNode::isDestroyed() const
{
    return false; // by default
}
