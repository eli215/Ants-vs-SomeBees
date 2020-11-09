
#ifndef ANTS_VS_SOME_BEES_LONGTHROWER_H
#define ANTS_VS_SOME_BEES_LONGTHROWER_H

#include "Thrower.h"

class LongThrower : public Thrower {
public:
    LongThrower(Space* location = nullptr);
    void act() override;

    static const std::string BASE_NAME;     // = "LongThrower"
    static const std::string BASE_ABBREV;
    static const int BASE_FOOD_COST = 3;
    static const int BASE_MAX_ARMOR = 1;
    static const int BASE_ATTACK_POWER = 1;
    static const int BASE_MIN_ATTACK_RANGE = 4;
    static const int BASE_MAX_ATTACK_RANGE = 999999;
    static const bool BASE_TARGETABILITY = true;
    static const int BASE_ACTION_PHASE = 1;
};


#endif //ANTS_VS_SOME_BEES_LONGTHROWER_H
