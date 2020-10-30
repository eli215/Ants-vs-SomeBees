
#ifndef INC_5_ANT_H
#define INC_5_ANT_H


#include "../Unit.h"

class Ant : public Unit {
protected:
    int foodCost;

public:
    Ant();
    Ant(int);

    /* Getters & Setters */
    int getFoodCost() const;
    void setFoodCost(int);

};


#endif //INC_5_ANT_H
