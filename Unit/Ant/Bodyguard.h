
#ifndef ANTS_VS_SOME_BEES_BODYGUARD_H
#define ANTS_VS_SOME_BEES_BODYGUARD_H

#include "Ant.h"

class Bodyguard : public Ant {
public:
    Bodyguard(Space* location = nullptr);
    void act() override;

    static const std::string BASE_NAME;     // = "Bodyguard"
    static const std::string BASE_ABBREV;   // = "Bodyguard"
    static const int BASE_FOOD_COST = 4;
    static const int BASE_MAX_ARMOR = 2;
    static const int BASE_TARGETABILITY = true;
    static const int BASE_ACTION_PHASE = 1;
protected:

};


#endif //ANTS_VS_SOME_BEES_BODYGUARD_H
