#ifndef CATEGORY_H_INCLUDED
#define CATEGORY_H_INCLUDED

namespace Category
{
    enum Type
    {
        None = 0,
        LowerScene = 1 << 0,
        UpperScene = 1 << 1,
        PlayerActor = 1 << 2,
        EnemyActor = 1 << 3,
        AlliedProjectile = 1 << 4,

    };
}

#endif // CATEGORY_H_INCLUDED
