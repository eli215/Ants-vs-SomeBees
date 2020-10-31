
#include "Space.h"
#include "Unit/Ant/Ant.h"
#include "Unit/Bee/Bee.h"

Space::Space() : coordinates() {

}


const int *Space::getCoordinates() const {
    return coordinates;
}

const std::vector<Ant *> &Space::getAnts() const {
    return ants;
}

void Space::setAnts(const std::vector<Ant *> &ants) {
    this->ants = ants;
}

const std::vector<Bee *> &Space::getBees() const {
    return bees;
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

Space *Space::getNext() const {
    return next;
}

void Space::setNext(Space *next) {
    this->next = next;
}

void Space::move() {
    Bee* b;
    b->move();

}


