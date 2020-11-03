
#include "Bodyguard.h"

Bodyguard::Bodyguard(Space *location)
    : Ant(BASE_MAX_ARMOR,BASE_MAX_ARMOR, location, BASE_TARGETABILITY,BASE_FOOD_COST, BASE_ACTION_PHASE) {

}

void Bodyguard::act() {
    //Ant::act();
}
