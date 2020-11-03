
#include <iostream>
#include "ShortThrower.h"

const std::string ShortThrower::BASE_NAME("ShortThrower");

ShortThrower::ShortThrower(Space *location)
: Thrower(BASE_NAME, BASE_MAX_ARMOR, BASE_MAX_ARMOR, location, BASE_TARGETABILITY,
          BASE_FOOD_COST, BASE_ACTION_PHASE, BASE_ATTACK_POWER, BASE_MIN_ATTACK_RANGE, BASE_MAX_ATTACK_RANGE) {

}


void ShortThrower::act() {
    Bee* firstTarget = enemyInRange();
    if (!firstTarget)
        return;     // return if no target(s) in range
    int damageInflicted = 0;
    for (int i = 0; i < firstTarget->getLocation()->getBees().size(); i++) {
        Bee* target = firstTarget->getLocation()->getBees()[i];
        if (attack(target))
            damageInflicted += attackPower;
    }
    std::cout << "ShortThrower Ant inflicts " << damageInflicted << " damage on nearby Bee(s).\n";
}