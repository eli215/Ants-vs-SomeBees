
#ifndef ANTS_VS_SOME_BEES_HARVESTER_H
#define ANTS_VS_SOME_BEES_HARVESTER_H


#include "Ant.h"

class Harvester : public Ant {
public:
    Harvester(Space* location = nullptr);

    void act() override;
    int getFoodProduction() const;
    void setFoodProduction(int foodProduction);

    static const std::string BASE_NAME;     // = "Harvester"
    static const int BASE_FOOD_COST = 2;
    static const int BASE_MAX_ARMOR = 1;
    static const int BASE_TARGETABILITY = true;
    static const int BASE_ACTION_PHASE = 1;
    static const int BASE_FOOD_PRODUCTION = 1;

protected:
    int foodProduction;

};


#endif //ANTS_VS_SOME_BEES_HARVESTER_H
