
#ifndef ANTS_VS_SOME_BEES_SHORTTHROWER_H
#define ANTS_VS_SOME_BEES_SHORTTHROWER_H

#include "Thrower.h"

class ShortThrower : public Thrower {
public:
    ShortThrower(Space* location = nullptr);
    void act() override;

    static const int BASE_FOOD_COST = 3;
    static const int BASE_MAX_ARMOR = 1;
    static const int BASE_TARGETABILITY = true;
    static const int BASE_MIN_ATTACK_RANGE = 0;
    static const int BASE_MAX_ATTACK_RANGE = 2;
    static const int BASE_ATTACK_POWER = 1;
    static const int BASE_ACTION_PHASE = 1;
};


#endif //ANTS_VS_SOME_BEES_SHORTTHROWER_H
