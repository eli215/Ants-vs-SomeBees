
#ifndef ANTS_VS_SOMEBEES_SPACE_H
#define ANTS_VS_SOMEBEES_SPACE_H

#include <vector>
//#include "Unit/Ant/Ant.h"
//#include "Unit/Bee/Bee.h"
class Ant;
class Bee;

class Space {
protected:
    const int coordinates[2];       // coordinates cannot be changed after initialization
    std::vector<Ant*> ants;
    std::vector<Bee*> bees;
    bool blocked;
    Space *next;
public:
    Space *getNext() const;

    void setNext(Space *next);

public:
    Space();

    void move();

    /* Getters & Setters */
    const int *getCoordinates() const;

    const std::vector<Ant *> &getAnts() const;
    void setAnts(const std::vector<Ant *> &ants);

    const std::vector<Bee *> &getBees() const;
    void setBees(const std::vector<Bee *> &bees);

    bool isBlocked() const;
    void setBlocked(bool blocked);
};


#endif //ANTS_VS_SOMEBEES_SPACE_H
