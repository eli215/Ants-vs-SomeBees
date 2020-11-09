
#include <iostream>
#include "Fire.h"
#include "../Bee/Bee.h"

const std::string Fire::BASE_NAME("Fire");
const std::string Fire::BASE_ABBREV("Fire");

// default constructor (location is default-null)
Fire::Fire(Space* location) :
        Ant(BASE_NAME, BASE_ABBREV, BASE_MAX_ARMOR, BASE_MAX_ARMOR, location, BASE_TARGETABILITY, BASE_FOOD_COST, BASE_ACTION_PHASE) {
    // determine targets based on provided location
    if (location) {
        this->targets.reserve(location->getBees().size());
        for (int i = 0; i < location->getBees().size(); i++) {
            targets.push_back(location->getBees()[i]);
        }
    }
}

void Fire::act() {
    if (isAlive())      // only act if this unit has died
        return;
    // all bees which were sharing the space have now exploded
    int beesSlain = 0;
    for (int i = 0; i < targets.size(); i++) {
        if (attack(targets[i]))
            beesSlain++;
    }
    std::cout << "Fire Ant combusts upon being slain, incinerating " << beesSlain << " nearby Bee(s).\n";
}

bool Fire::attack(Bee *target) {
    bool success = true;
    if (target->isAlive())
        target->setArmor(0);        // this bee is now dead
    else    // attack failed if unit is already dead
        success = false;
    return success;
}
