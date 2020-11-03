
#include <iostream>
#include "LongThrower.h"

LongThrower::LongThrower(Space *location)
        : Thrower(BASE_MAX_ARMOR, BASE_MAX_ARMOR, location, BASE_TARGETABILITY,
                  BASE_FOOD_COST, BASE_ACTION_PHASE, BASE_ATTACK_POWER, BASE_MIN_ATTACK_RANGE, BASE_MAX_ATTACK_RANGE) {
}

void LongThrower::act() {
    Bee* firstTarget = enemyInRange();
    if (!firstTarget)
        return;     // return if no target(s) in range
    int damageInflicted = 0;
    for (int i = 0; i < firstTarget->getLocation()->getBees().size(); i++) {
        Bee* target = firstTarget->getLocation()->getBees()[i];
        if (attack(target))
            damageInflicted += attackPower;
    }
    std::cout << "LongThrower Ant inflicts " << damageInflicted << " damage on distant Bee(s).\n";
}


