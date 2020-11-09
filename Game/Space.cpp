
#include "Space.h"
//#include "Unit/Ant/Ant.h"
#include "../Unit/Ant/Bodyguard.h"
#include "../Unit/Bee/Bee.h"
#include "../Unit/Bee/BasicBee.h"
#include <typeinfo>
#include <iostream>

Space::Space() {
    //blocked = false;
    last = nullptr;
    next = nullptr;
    unitCount = 0;
}

Space::~Space() {
    // delete Ants allocated with 'new'
    for (int i = 0; i < ants.size(); i++) {
        delete ants[i];
    }

    // delete Bees allocated with 'new'
    for (int i = 0; i < bees.size(); i++) {
        delete bees[i];
    }
}


const int *Space::getCoordinates() const {
    return coordinates;
}

std::vector<Ant *> &Space::getAnts() {
    return ants;
}

void Space::insertAnt(Ant* ant) {
    if (typeid(Bodyguard) == typeid(*ant)) {
        ants.insert(ants.begin(), ant);     // bodyguard goes before other ant(s)
    } else {
        ants.push_back(ant);
    }
    unitCount++;
}

void Space::setAnts(const std::vector<Ant *> &ants) {
    this->ants = ants;
}

std::vector<Bee *> &Space::getBees() {
    return bees;
}

void Space::insertBee(Bee* bee) {
    bees.push_back(bee);
    unitCount++;
}

void Space::setBees(const std::vector<Bee *> &bees) {
    this->bees = bees;
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
        curLoc->unitCount--;
        newLoc->unitCount++;
        std::cout << "Bee moves from [" << curLoc->getCol() + 1 << "] --> [" << newLoc->getCol() + 1 << "].\n";
    }
}

Space *Space::getLast() const {
    return last;
}

void Space::setLast(Space *last) {
    Space::last = last;
}

int Space::getRow() const {
    return coordinates[0];
}

int Space::getCol() const {
    return coordinates[1];
}

void Space::setCoordinates(int row, int col) {
    coordinates[0] = row;
    coordinates[1] = col;
}

int Space::getUnitCount() const {
    return unitCount;
}

void Space::setUnitCount(int unitCount) {
    this->unitCount = unitCount;
}
