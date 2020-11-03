
#include "Space.h"
//#include "Unit/Ant/Ant.h"
#include "../Unit/Ant/Bodyguard.h"
#include "../Unit/Bee/Bee.h"
#include "../Unit/Bee/BasicBee.h"
#include <typeinfo>

Space::Space() {
    blocked = false;
    last = nullptr;
    next = nullptr;
}


const int *Space::getCoordinates() const {
    return coordinates;
}

const std::vector<Ant *> &Space::getAnts() const {
    return ants;
}

void Space::insertAnt(Ant* ant) {
    if (typeid(Bodyguard) == typeid(ant)) {
        ants.insert(ants.begin(), ant);     // bodyguard goes before other ant(s)
    } else {
        ants.push_back(ant);
    }
}

void Space::setAnts(const std::vector<Ant *> &ants) {
    this->ants = ants;
}

std::vector<Bee *> &Space::getBees() {
    return bees;
}

void Space::insertBee(Bee* bee) {
    bees.push_back(bee);
}

void Space::setBees(const std::vector<Bee *> &bees) {
    this->bees = bees;
}

bool Space::isBlocked() const {
    return blocked;
}

void Space::setBlocked(bool blocked) {
    this->blocked = blocked;
}

Space *Space::getNext() {
    return next;
}

void Space::setNext(Space *next) {
    this->next = next;
}

void Space::move(Bee* bee) {
    Space* curLoc = bee->getLocation();
    Space* newLoc = (bee->isNegativeMoveDirection()) ? curLoc->getLast() : curLoc->getNext();
    int beeInd = 0;
    for (int i = 0; i < curLoc->getBees().size(); i++) {        // find this bee's index in the Bee vector
        if (bee == curLoc->getBees()[i]) {
            beeInd = i;
            break;
        }
    }
    if (newLoc) {
        curLoc->getBees().erase(curLoc->getBees().begin() + beeInd);    // remove the bee from previous location
        bee->setLocation(newLoc);        // update its location to new Space
        newLoc->insertBee(bee);      // insert bee into new location
    }
}

Space *Space::getLast() const {
    return last;
}

void Space::setLast(Space *last) {
    Space::last = last;
}


