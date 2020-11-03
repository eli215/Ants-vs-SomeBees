
#ifndef ANTS_VS_SOME_BEES_THROWER_H
#define ANTS_VS_SOME_BEES_THROWER_H

#include "../Ant.h"
#include "../../Bee/Bee.h"


class Thrower : public Ant {
protected:
    int attackPower;
    int attackRange;

public:
    Thrower(Space* location = nullptr);

    static const int BASE_ATTACK_POWER = 1;
    static const int BASE_ATTACK_RANGE = 0;
    static const int BASE_MAX_ARMOR = 1;
    static const int BASE_FOOD_COST = 4;
    static const bool BASE_TARGETABILITY = true;
    static const int BASE_ACTION_PHASE = 1;

    void act() override;

    Bee* enemyInRange();
    void attack(Bee* target);
};


#endif //ANTS_VS_SOME_BEES_THROWER_H
