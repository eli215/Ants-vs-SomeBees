
#include <iostream>
#include "BasicBee.h"

const std::string BasicBee::BASE_NAME("BasicBee");

// Default constructor (location is default-null)
BasicBee::BasicBee(Space *location)
    : Bee(BASE_NAME, BASE_MAX_ARMOR, BASE_MAX_ARMOR, location, BASE_TARGETABILITY, BASE_MOVE_SIZE, BASE_NEGATIVE_MOVE_DIRECTION, BASE_ACTION_PHASE) {
    this->attackPower = BASE_ATTACK_POWER;
    this->attackRange = BASE_ATTACK_RANGE;
}

void BasicBee::act() {
    Ant* target = enemyInRange();
    if (target) {       // if target != null, we have a target
        if (attack(target))
            std::cout << "Bee inflicts " << attackPower << " damage on " << target->getName() << ".\n";
    }
}

Ant* BasicBee::enemyInRange() {
    Space *space = location;    // start with current space
    // for each space within range
    for (int i = 0; i <= attackRange && space; i++, space = space->getLast()) {
        // for each ant at this space
        for (int j = 0; j < space->getAnts().size(); j++) {
            if (space->getAnts()[j]->isTargetable())
                return space->getAnts()[j];         // return closest targetable ant that is within range
        }
    }
    return nullptr;     // return null if no targetable enemies are in range
}

bool BasicBee::attack(Ant *target) {
    bool success = true;
    if (target->isAlive())
        target->setArmor(target->getArmor() - attackPower);     // inflict damage onto the target by reducing its armor
    else
        success = false;
    return success;
}
