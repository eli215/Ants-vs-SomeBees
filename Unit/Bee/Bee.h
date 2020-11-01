
#ifndef ANTS_VS_SOMEBEES_BEE_H
#define ANTS_VS_SOMEBEES_BEE_H

#include "../Unit.h"

// abstract Bee class
class Bee : public Unit {
protected:

public:
    Bee(Space* location = nullptr);     // default constructor (w/ default location arg)
    Bee(int armor, int maxArmor, Space* location, bool targetable);

    virtual void act() = 0;

    void move();
};


#endif //ANTS_VS_SOMEBEES_BEE_H
