
#ifndef ANTS_VS_SOMEBEES_BEE_H
#define ANTS_VS_SOMEBEES_BEE_H

#include "../Unit.h"

// abstract Bee class
class Bee : public Unit {
protected:
    int moveSize;
    bool negativeMoveDirection;

public:
    Bee(Space* location = nullptr);     // default constructor (w/ default location arg)
    Bee(std::string name, std::string abbrev, int armor, int maxArmor, Space* location, bool targetable, int moveSize, bool negMoveDir, int actionPhase);

    virtual void act() = 0;

    //void move();  // Space class handles movement now

    bool isNegativeMoveDirection() const;

    void setNegativeMoveDirection(bool negativeMoveDirection);

    int getMoveSize() const;

    void setMoveSize(int moveSize);
};


#endif //ANTS_VS_SOMEBEES_BEE_H

