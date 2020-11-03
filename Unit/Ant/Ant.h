
#ifndef ANTS_VS_SOMEBEES_ANT_H
#define ANTS_VS_SOMEBEES_ANT_H


#include "../Unit.h"

// abstract Ant class
class Ant : public Unit {
protected:
    int foodCost;

public:
    Ant(Space* location = nullptr);     // default constructor (w/ default location arg)
    Ant(int armor, int maxArmor, Space* location, bool targetable, int foodCost, int actionPhase);

    virtual void act();

    /* Getters & Setters */
    int getFoodCost();
    void setFoodCost(int foodCost);
};


#endif //ANTS_VS_SOMEBEES_ANT_H
