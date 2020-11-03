
#include "Thrower.h"

Thrower::Thrower(Space* location) :
    Ant(BASE_MAX_ARMOR, BASE_MAX_ARMOR, location, BASE_TARGETABILITY, BASE_FOOD_COST, BASE_ACTION_PHASE) {
    this->attackPower = BASE_ATTACK_POWER;
    this->attackRange = BASE_ATTACK_RANGE;
}

void Thrower::act() {
    Bee* target = enemyInRange();
    if (target) {       // if target != null, we have a target
        attack(target);
    }
}

Bee* Thrower::enemyInRange() {
    Space *space = location;    // start with current space
    // for each space within range
    for (int i = 0; i <= attackRange && space; i++, space = space->getNext()) {
        // for each bee at this space
        for (int j = 0; j < space->getBees().size(); j++) {
            if (space->getBees()[j]->isTargetable())
                return space->getBees()[j];         // return closest targetable bee that is within range
        }
    }
    return nullptr;     // return null if no targetable enemies are in range
}

// note: assumes target is non-null
void Thrower::attack(Bee* target) {
    if (target->isAlive())
        target->setArmor(target->getArmor() - attackPower);     // inflict damage onto the target by reducing its armor
}

