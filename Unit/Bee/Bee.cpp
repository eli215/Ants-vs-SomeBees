
#include "Bee.h"

// default constructor - shouldn't be used
Bee::Bee(Space* location) : Unit(0, 0, location, false, 0) {

}

Bee::Bee(int armor, int maxArmor, Space *location, bool targetable, int moveSize, int actionPhase)
        : Unit(armor, maxArmor, location, targetable, actionPhase) {
    this->moveSize = moveSize;
}

void Bee::act() {

}

// moves in negative direction
void Bee::move() {
    for (int i = 0; i < moveSize; i++) {
        if (location->getLast()) {
            location = location->getLast();
        }
    }
}

