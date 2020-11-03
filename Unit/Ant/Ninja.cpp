
#include <iostream>
#include "Ninja.h"
#include "../Bee/Bee.h"

/*
Ninja::Ninja(int armor, int maxArmor, Space *location, bool targetable, int foodCost, std::vector<Bee *> targets)
    : Ant(armor, maxArmor, location, targetable, foodCost) {
    this->targets = targets;
} */

// default constructor (location is default-null)
Ninja::Ninja(Space* location) :
Ant(BASE_MAX_ARMOR, BASE_MAX_ARMOR, location, BASE_TARGETABILITY, BASE_FOOD_COST, BASE_ACTION_PHASE) {
    this->attackPower = BASE_ATTACK_POWER;
    // determine targets based on provided location
    if (location) {
        this->targets.reserve(location->getBees().size());
        for (int i = 0; i < location->getBees().size(); i++) {
            targets.push_back(location->getBees()[i]);
        }
    }
}

void Ninja::act() {
    // mark whether any existing targets have passed by; add any new bees to targets
    bool hasPassed[targets.size()];
    for (int i = 0, foundMatch = 0; i < location->getBees().size(); i++) {  // for each bee at this space
        Bee *bee = location->getBees()[i];
        for (int j = 0; !foundMatch && j < targets.size(); j++) {   // for each existing target
            if (targets[j] == bee) {    // check if this bee is an existing target
                hasPassed[j] = false;
                foundMatch = true;
            }
        }
        if (!foundMatch) {      // we haven't seen this bee before; add it to targets
            targets.push_back(bee);
        }
    }
    int damageInflicted = 0;
    for (int i = 0; i < targets.size(); i++) {
        if (hasPassed[i]) {     // if this bee made the mistake of crossing a Ninja
            if (attack(targets[i]))           // attack the bee
                damageInflicted++;
            targets.erase(targets.begin() + i);       // remove the bee
        }
    }
    std::cout << "Ninja Ant silently inflicts " << damageInflicted << " damage on passing Bee(s).\n";
}

bool Ninja::attack(Bee *target) {
    bool success = true;
    if (target->isAlive())
        target->setArmor(target->getArmor() - attackPower);
    else    // attack failed if unit is already dead
        success = false;
    return success;
}
