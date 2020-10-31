
#ifndef ANTS_VS_SOMEBEES_BEE_H
#define ANTS_VS_SOMEBEES_BEE_H

#include "../Unit.h"

// abstract Bee class
class Bee : public Unit {
protected:

public:
    Bee();
    virtual void act() = 0;


    void move();
};


#endif //ANTS_VS_SOMEBEES_BEE_H
