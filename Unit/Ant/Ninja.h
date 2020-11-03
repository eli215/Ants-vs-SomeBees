
#ifndef ANTS_VS_SOMEBEES_NINJA_H
#define ANTS_VS_SOMEBEES_NINJA_H

#include "Ant.h"


class Ninja : public Ant {
protected:
    int attackPower;
    std::vector<Bee*> targets;
public:
    Ninja(Space* location = nullptr);   // default constructor (optional location parameter)

    static const std::string BASE_NAME;     // = "Ninja"
    static const int BASE_ATTACK_POWER = 1;
    static const int BASE_MAX_ARMOR = 1;
    static const bool BASE_TARGETABILITY = false;
    static const int BASE_FOOD_COST = 6;
    static const int BASE_ACTION_PHASE = 3;

    void act() override;
    bool attack(Bee* target);
};


#endif //ANTS_VS_SOMEBEES_NINJA_H
