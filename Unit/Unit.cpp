

#include "Unit.h"

/* Constructors */

Unit::Unit() : maxArmor(0) {
    armor = 0;
    location = nullptr;
    targetable = false;
    actionPhase = 0;
}

Unit::Unit(std::string name, int armor, int maxArmor, Space *location, bool targetable, int actionPhase) : maxArmor(maxArmor) {
    this->name = name;
    this->armor = armor;
    this->location = location;
    this->targetable = targetable;
    this->actionPhase = actionPhase;
}

/* Getters & Setters */

int Unit::getArmor() const {
    return armor;
}

void Unit::setArmor(int value) {
    this->armor = value;
}

int Unit::getMaxArmor() const {
    return maxArmor;
}

bool Unit::isTargetable() const {
    return targetable;
}

void Unit::setTargetable(bool targetable) {
    this->targetable = targetable;
}

Space *Unit::getLocation() const {
    return location;
}

void Unit::setLocation(Space *location) {
    this->location = location;
}

bool Unit::isAlive() const {
    return (armor > 0);
}

int Unit::getActionPhase() const {
    return actionPhase;
}

void Unit::setActionPhase(int actionPhase) {
    Unit::actionPhase = actionPhase;
}

const std::string &Unit::getName() const {
    return name;
}

void Unit::setName(const std::string &name) {
    this->name = name;
}


