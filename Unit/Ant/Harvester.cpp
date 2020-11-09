
#include <iostream>
#include "Harvester.h"

const std::string Harvester::BASE_NAME("Harvester");
const std::string Harvester::BASE_ABBREV("Harvester");

Harvester::Harvester(Space *location)
    : Ant(BASE_NAME, BASE_ABBREV, BASE_MAX_ARMOR,BASE_MAX_ARMOR, location, BASE_TARGETABILITY,BASE_FOOD_COST, BASE_ACTION_PHASE) {
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
    std::cout << "Harvester produced " << foodProduction << " food.\n";
}
