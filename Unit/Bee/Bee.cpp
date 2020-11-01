
#include "Bee.h"

// default constructor - shouldn't be used
Bee::Bee(Space* location) : Unit(0, 0, location, false) {

}

Bee::Bee(int armor, int maxArmor, Space *location, bool targetable)
        : Unit(armor, maxArmor, location, targetable) {

}

void Bee::act() {

}

void Bee::move() {

}

