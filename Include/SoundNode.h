#ifndef SOUNDNODE_H
#define SOUNDNODE_H

#include "SceneNode.h"
#include "SoundPlayer.h"

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
