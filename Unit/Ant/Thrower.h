
#ifndef ANTS_VS_SOME_BEES_THROWER_H
#define ANTS_VS_SOME_BEES_THROWER_H

#include "Ant.h"


class Thrower : public Ant {
protected:
    int attackPower;

public:
    void act() override;


};


#endif //ANTS_VS_SOME_BEES_THROWER_H
