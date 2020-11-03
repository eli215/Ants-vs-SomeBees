
#include "Fire.h"
#include "../Bee/Bee.h"

// default constructor (location is default-null)
Fire::Fire(Space* location) :
        Ant(BASE_MAX_ARMOR, BASE_MAX_ARMOR, location, BASE_TARGETABILITY, BASE_FOOD_COST, BASE_ACTION_PHASE) {
    // determine targets based on provided location
    if (location) {
        this->targets.reserve(location->getBees().size());
        for (int i = 0; i < location->getBees().size(); i++) {
            targets.push_back(location->getBees()[i]);
        }
    }
}

void Fire::act() {
    if (isAlive())      // only act upon being killed
        return;
    // all bees which were sharing the space have now exploded
    for (int i = 0; i < targets.size(); i++) {
        attack(targets[i]);
    }
}

void Fire::attack(Bee *target) {
    if (target->isAlive())
        target->setArmor(0);        // this bee is now dead
}
