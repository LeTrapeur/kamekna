#include <FRK2D/SoundNode.hpp>

SoundNode::SoundNode(SoundPlayer& player):
    SceneNode(),
    m_sounds(player)
{}

void SoundNode::playSound(SoundEffects::ID sound)
{
    m_sounds.play(sound);
}

unsigned int SoundNode::getCategory() const
{
    return Category::SoundEffect;
}
