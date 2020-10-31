
#include "Ninja.h"

/*
Ninja::Ninja(int armor, int maxArmor, Space *location, bool targetable, int foodCost, std::vector<Bee *> watchlist)
    : Ant(armor, maxArmor, location, targetable, foodCost) {
    this->watchlist = watchlist;
} */

// default constructor (location is default-null)
Ninja::Ninja(Space* location) :
Ant(BASE_MAX_ARMOR, BASE_MAX_ARMOR, location, BASE_TARGETABILITY, BASE_FOOD_COST) {
    this->attackPower = BASE_ATTACK_POWER;
    // determine watchlist based on provided location
    if (location) {
        this->watchlist.reserve(location->getBees().size());
        for (int i = 0; i < location->getBees().size(); i++) {
            watchlist.push_back(location->getBees()[i]);
        }
    }
}

void Ninja::act() {
    // detect whether any potential targets have passed by, add any new bees to watchlist
    bool hasPassed[watchlist.size()];

    for (int i = 0, foundMatch = 0; i < location->getBees().size(); i++) {
        Bee *bee = location->getBees()[i];
        // check if this bee is already being watched, or if it's new
        for (int j = 0; !foundMatch && j < watchlist.size(); j++) {
            if (watchlist[j] == bee) {
                hasPassed[j] = false;       // this bee was wise enough to stay put
                foundMatch = true;
            }
        }
        if (!foundMatch) {      // we haven't seen this bee before; add it to targets
            watchlist.push_back(bee);
        }
    }

    for (int i = 0; i < watchlist.size(); i++) {
        if (hasPassed[i]) {     // if this bee made the mistake of crossing a Ninja
            attack(watchlist[i]);           // attack the bee
            watchlist.erase(watchlist.begin() + i);       // remove the bee
        }
    }
}

void Ninja::attack(Bee *target) {
    if (target->isAlive())
        target->setArmor(target->getArmor() - attackPower);
}
