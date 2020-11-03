
#include "Harvester.h"

Harvester::Harvester(Space *location)
    : Ant(BASE_MAX_ARMOR,BASE_MAX_ARMOR, location, BASE_TARGETABILITY,BASE_FOOD_COST, BASE_ACTION_PHASE) {
    this->foodProduction = BASE_FOOD_PRODUCTION;
}

int Harvester::getFoodProduction() const {
    return foodProduction;
}

void Harvester::setFoodProduction(int foodProduction) {
    Harvester::foodProduction = foodProduction;
}

void Harvester::act() {
    //Ant::act();
}
