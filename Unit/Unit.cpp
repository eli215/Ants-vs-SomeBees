

#include "Unit.h"

/* Constructors */

Unit::Unit() {
    armor = 0;
    maxArmor = 0;
}

Unit::Unit(int armor, int maxArmor) {
    this->armor = armor;
    this->maxArmor = maxArmor;
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

void Unit::setMaxArmor(int value) {
    this->maxArmor = value;
}

