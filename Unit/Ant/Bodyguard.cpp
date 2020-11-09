
#include "Bodyguard.h"

const std::string Bodyguard::BASE_NAME("Bodyguard");
const std::string Bodyguard::BASE_ABBREV("Bodyguard");

Bodyguard::Bodyguard(Space *location)
    : Ant(BASE_NAME, BASE_ABBREV, BASE_MAX_ARMOR,BASE_MAX_ARMOR, location, BASE_TARGETABILITY,BASE_FOOD_COST, BASE_ACTION_PHASE) {

}

void Bodyguard::act() {
    //Ant::act();
}
