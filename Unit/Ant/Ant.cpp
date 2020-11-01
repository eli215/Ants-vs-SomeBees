
#include "Ant.h"

/* Constructors */

// default constructor - shouldn't be used
Ant::Ant(Space* location) : Unit(0, 0, location, false) {
    foodCost = 0;
}

Ant::Ant(int armor, int maxArmor, Space* location, bool targetable, int foodCost)
    : Unit(armor, maxArmor, location, targetable) {
    this->foodCost = foodCost;
}

/* Getters & Setters */

int Ant::getFoodCost() const {
    return foodCost;
}

void Ant::setFoodCost(int foodCost) {
    this->foodCost = foodCost;
}
