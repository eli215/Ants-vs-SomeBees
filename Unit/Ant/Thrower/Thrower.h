
#ifndef ANTS_VS_SOME_BEES_THROWER_H
#define ANTS_VS_SOME_BEES_THROWER_H

#include "../Ant.h"
#include "../../Bee/Bee.h"


class Thrower : public Ant {
protected:
    int attackPower;
    int minAttackRange;
    int maxAttackRange;

public:
    Thrower(Space* location = nullptr);
    Thrower(std::string name, int armor, int maxArmor, Space* location, bool targetability, int foodCost,
            int actionPhase, int attackPower, int minAttackRange, int maxAttackRange);

    static const std::string BASE_NAME;     // = "Thrower"
    static const int BASE_ATTACK_POWER = 1;
    static const int BASE_MIN_ATTACK_RANGE = 0;
    static const int BASE_MAX_ATTACK_RANGE = 0;
    static const int BASE_MAX_ARMOR = 1;
    static const int BASE_FOOD_COST = 4;
    static const bool BASE_TARGETABILITY = true;
    static const int BASE_ACTION_PHASE = 1;

    void act() override;

    virtual Bee* enemyInRange();
    bool attack(Bee* target);

    int getAttackPower() const;
    void setAttackPower(int attackPower);

    int getMaxAttackRange() const;
    void setMaxAttackRange(int maxAttackRange);

    int getMinAttackRange() const;
    void setMinAttackRange(int minAttackRange);
};


#endif //ANTS_VS_SOME_BEES_THROWER_H
