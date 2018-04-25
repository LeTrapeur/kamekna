#ifndef ACTOR_H
#define ACTOR_H

#include <FRK2D/Entity.hpp>
#include <FRK2D/ResourceHolder.hpp>
#include <FRK2D/TextNode.hpp>
#include <FRK2D/Animation.hpp>
#include <FRK2D/AnimatedSprite.hpp>

class Actor : public Entity
{
    public:
        enum Type
        {
            Hero,
            Enemy,
            Allied,
        };

    public:
        explicit                Actor(Type type, const TextureHolder& textures, const FontHolder& fonts, b2World& world);

        void                    goLeft();
        void                    walkLeft();
        void                    goRight();
        void                    walkRight();
        void                    goUp();
        void                    walkUp();
        void                    goDown();
        void                    walkDown();
        void                    lookLeft();
        void                    lookRight();
        void                    lookUp();
        void                    lookDown();

        virtual unsigned int    getCategory() const;

        float                   getLife() const;
        void                    takeDamage(unsigned int damage);
        void                    updateText();
        // TODO delay with animation
        virtual bool            isDestroyed() const;


    private:
        virtual void            drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
        void                    checkMove(sf::Time dt, CommandQueue& commands);
        void                    updateLookingDirection();

        static b2Body*          createBody(b2World& world);

    protected:
        virtual void            updateCurrent(sf::Time dt, CommandQueue& commands);

    protected:
        enum LookingOrientation
        {
            Left,
            Right,
            Up,
            Down,
            Count,
        };

    protected:
        AnimatedSprite          m_animatedSprite;
        Animation               m_currentAnim;
        Animation               m_walkLeft;
        Animation               m_walkRight;
        Animation               m_walkUp;
        Animation               m_walkDown;

        int                     m_numFootContacts;

        Type                    m_type;

        int                     m_life;
        TextNode*               m_infoDisplay;

        LookingOrientation      m_lookingOrientation;

        bool                    m_isGoingLeft;
        bool                    m_isGoingRight;
        bool                    m_isGoingUp;
        bool                    m_isGoingDown;
};

#endif // ACTOR_H
