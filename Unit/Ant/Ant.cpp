
#include "Ant.h"

/* Constructors */

Ant::Ant() {
    foodCost = 0;
}

Ant::Ant(int foodCost) {
    this->foodCost = foodCost;
}

/* Getters & Setters */

int Ant::getFoodCost() const {
    return foodCost;
}

void Ant::setFoodCost(int foodCost) {
    this->foodCost = foodCost;
}
