
#ifndef ANTS_VS_SOME_BEES_FIRE_H
#define ANTS_VS_SOME_BEES_FIRE_H


#include "Ant.h"


class Fire : public Ant {
protected:
    //int attackPower;
    std::vector<Bee*> targets;
public:
    Fire(Space* location = nullptr);   // default constructor (optional location parameter)

    //static const int BASE_ATTACK_POWER = 1;
    static const int BASE_MAX_ARMOR = 1;
    static const bool BASE_TARGETABILITY = true;
    static const int BASE_FOOD_COST = 4;
    static const int BASE_ACTION_PHASE = 3;

    void act() override;
    void attack(Bee* target);
};


#endif //ANTS_VS_SOME_BEES_FIRE_H
