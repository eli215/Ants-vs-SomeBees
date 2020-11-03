
#ifndef ANTS_VS_SOMEBEES_BASICBEE_H
#define ANTS_VS_SOMEBEES_BASICBEE_H

#include "Bee.h"
#include "../Ant/Ant.h"

class BasicBee : public Bee {
public:
    BasicBee(Space* location = nullptr);

    static const std::string BASE_NAME;     // = "BasicBee"
    static const int BASE_ATTACK_POWER = 1;
    static const int BASE_ATTACK_RANGE = 0;
    static const int BASE_MAX_ARMOR = 1;
    static const bool BASE_TARGETABILITY = true;
    static const int BASE_MOVE_SIZE = 1;
    static const bool BASE_NEGATIVE_MOVE_DIRECTION = true;
    static const int BASE_ACTION_PHASE = 3;

    void act() override;
    bool attack(Ant* target);
protected:
    int attackPower;
    int attackRange;

    Ant *enemyInRange();
};


#endif //ANTS_VS_SOMEBEES_BASICBEE_H
