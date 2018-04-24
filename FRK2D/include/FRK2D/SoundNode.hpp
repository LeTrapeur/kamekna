#ifndef SOUNDNODE_H
#define SOUNDNODE_H

#include <FRK2D/SceneNode.hpp>
#include <FRK2D/SoundPlayer.hpp>

class SoundNode : public SceneNode
{
    public:
        explicit                    SoundNode(SoundPlayer& player);
        void                        playSound(SoundEffect::ID sound);

        virtual unsigned int        getCategory() const;

    private:
        SoundPlayer& m_sounds;
};

#endif // SOUNDNODE_H
