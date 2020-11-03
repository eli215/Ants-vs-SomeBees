
#include "Thrower.h"

Thrower::Thrower(Space* location) :
    Ant(BASE_MAX_ARMOR, BASE_MAX_ARMOR, location, BASE_TARGETABILITY, BASE_FOOD_COST, BASE_ACTION_PHASE) {
    this->attackPower = BASE_ATTACK_POWER;
    this->minAttackRange = BASE_MIN_ATTACK_RANGE;
    this->maxAttackRange = BASE_MAX_ATTACK_RANGE;
}

Thrower::Thrower(int armor, int maxArmor, Space *location, bool targetable, int foodCost,
                 int actionPhase, int attackPower, int minAttackRange, int maxAttackRange)
                 : Ant(armor, maxArmor, location, targetable, foodCost, actionPhase) {
    this->attackPower = attackPower;
    this->minAttackRange = minAttackRange;
    this->maxAttackRange = maxAttackRange;
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
    for (int i = 0; space && i <= maxAttackRange; i++, space = space->getNext()) {
        if (i < minAttackRange)
            continue;       // skip space if it's too close to attack
        // for each bee at this space
        for (int j = 0; j < space->getBees().size(); j++) {
            if (space->getBees()[j]->isTargetable())
                return space->getBees()[j];         // return closest targetable bee that is within range
        }
    }
    return nullptr;     // return null if no targetable enemies are in range
}

// note: assumes target is non-null
bool Thrower::attack(Bee* target) {
    bool success = true;
    if (target->isAlive())
        target->setArmor(target->getArmor() - attackPower);     // inflict damage onto the target by reducing its armor
    else
        success = false;
    return success;
}

int Thrower::getAttackPower() const {
    return attackPower;
}

void Thrower::setAttackPower(int attackPower) {
    this->attackPower = attackPower;
}

int Thrower::getMaxAttackRange() const {
    return maxAttackRange;
}

void Thrower::setMaxAttackRange(int maxAttackRange) {
    this->maxAttackRange = maxAttackRange;
}

int Thrower::getMinAttackRange() const {
    return minAttackRange;
}

void Thrower::setMinAttackRange(int minAttackRange) {
    this->minAttackRange = minAttackRange;
}

