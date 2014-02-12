#ifndef CATEGORY_H_INCLUDED
#define CATEGORY_H_INCLUDED

namespace Category
{
    enum Type
    {
        None = 0,
        LowerScene = 1 << 1,
        UpperScene = 1 << 0,
        PlayerActor = 1 << 2,
        EnemyActor = 1 << 3,
        AlliedProjectile = 1 << 4,
        EnemyProjectile = 1 << 5,
        SoundEffect = 1 << 6,

        Projectile = AlliedProjectile | EnemyProjectile,
        Actor = PlayerActor | EnemyActor,
        PhysicalObject = LowerScene,
    };
}

#endif // CATEGORY_H_INCLUDED
