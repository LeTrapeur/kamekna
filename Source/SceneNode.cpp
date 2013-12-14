#include "SceneNode.h"

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
