

#include "Unit.h"

/* Constructors */

Unit::Unit() : maxArmor(0) {
    armor = 0;
    location = nullptr;
    targetable = false;
}

Unit::Unit(int armor, int maxArmor, Space *location, bool targetable) : maxArmor(maxArmor) {
    this->armor = armor;
    this->location = location;
    this->targetable = targetable;
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

