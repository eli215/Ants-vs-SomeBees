
#include "Bee.h"

// default constructor - shouldn't be used
Bee::Bee(Space* location) : Unit("", 0, 0, location, false, 0) {
    moveSize = 0;
    negativeMoveDirection = true;
}

Bee::Bee(std::string name, int armor, int maxArmor, Space *location, bool targetable, int moveSize, bool negMoveDir, int actionPhase)
        : Unit(name, armor, maxArmor, location, targetable, actionPhase) {
    this->moveSize = moveSize;
    this->negativeMoveDirection = negMoveDir;
}

void Bee::act() {

}

// moves in negative direction
/*
void Bee::move() {
    for (int i = 0; i < moveSize; i++) {
        if (location->getLast()) {
            location = location->getLast();
        }
    }
} */

bool Bee::isNegativeMoveDirection() const {
    return negativeMoveDirection;
}

void Bee::setNegativeMoveDirection(bool negativeMoveDirection) {
    this->negativeMoveDirection = negativeMoveDirection;
}

int Bee::getMoveSize() const {
    return moveSize;
}

void Bee::setMoveSize(int moveSize) {
    this->moveSize = moveSize;
}

