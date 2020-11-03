
#include "Ant.h"

/* Constructors */

// default constructor - shouldn't be used
Ant::Ant(Space* location) : Unit(0, 0, location, false, 0) {
    foodCost = 0;
}

Ant::Ant(int armor, int maxArmor, Space* location, bool targetable, int foodCost, int actionPhase)
    : Unit(armor, maxArmor, location, targetable, actionPhase) {
    this->foodCost = foodCost;
}

/* Getters & Setters */

int Ant::getFoodCost() {
    return foodCost;
}

void Ant::setFoodCost(int foodCost) {
    this->foodCost = foodCost;
}

void Ant::act() {

}
