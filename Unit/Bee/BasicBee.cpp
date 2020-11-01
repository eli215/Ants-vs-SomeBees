
#include "BasicBee.h"

// Default constructor (location is default-null)
BasicBee::BasicBee(Space *location)
    : Bee(BASE_MAX_ARMOR, BASE_MAX_ARMOR, location, BASE_TARGETABILITY) {
    this->attackPower = BASE_ATTACK_POWER;
    this->attackRange = BASE_ATTACK_RANGE;
}

void BasicBee::act() {
    Ant* target = enemyInRange();
    if (target) {       // if target != null, we have a target
        attack(target);
    }
}

Ant* BasicBee::enemyInRange() {
    Space *space = location;    // start with current space
    // for each space within range
    for (int i = 0; i <= attackRange && space; i++, space = space->getNext()) {
        // for each ant at this space
        for (int j = 0; j < space->getAnts().size(); j++) {
            if (space->getAnts()[j]->isTargetable())
                return space->getAnts()[j];         // return closest targetable ant that is within range
        }
    }
    return nullptr;     // return null if no targetable enemies are in range
}

void BasicBee::attack(Ant *target) {

}
