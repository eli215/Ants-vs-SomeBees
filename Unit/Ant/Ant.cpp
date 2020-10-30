
#include "Ant.h"

Ant::Ant() {
    foodCost = 0;
}

Ant::Ant(int foodCost) {
    this->foodCost = foodCost;
}

int Ant::getFoodCost() const {
    return foodCost;
}

void Ant::setFoodCost(int value) {
    this->foodCost = value;
}
