
#ifndef INC_5_ANT_H
#define INC_5_ANT_H


#include "../Unit.h"

// abstract Ant class
class Ant : public Unit {
protected:
    int foodCost;

public:
    Ant();
    Ant(int foodCost);

    virtual void act() = 0;

    /* Getters & Setters */
    int getFoodCost() const;
    void setFoodCost(int foodCost);
};


#endif //INC_5_ANT_H
