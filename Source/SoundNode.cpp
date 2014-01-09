#include "SoundNode.h"

SoundNode::SoundNode(SoundPlayer& player):
    SceneNode(),
    m_sounds(player)
{}

void SoundNode::playSound(SoundEffect::ID sound)
{
    m_sounds.play(sound);
}

unsigned int SoundNode::getCategory() const
{
    return Category::SoundEffect;
}
