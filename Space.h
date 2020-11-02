
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
    Space *last;
public:
    Space *getLast() const;

    void setLast(Space *last);

protected:
    Space *next;
public:
    Space *getNext();

    void setNext(Space *next);

public:
    Space(const int coords[2] = nullptr);

    void move();

    /* Getters & Setters */
    const int *getCoordinates() const;

    const std::vector<Ant *> &getAnts() const;
    void setAnts(const std::vector<Ant *> &ants);

    const std::vector<Bee *> &getBees() const;
    void setBees(const std::vector<Bee *> &bees);

    bool isBlocked() const;
    void setBlocked(bool blocked);

    void insertAnt(Ant *ant);

    void insertBee(Bee *bee);
};


#endif //ANTS_VS_SOMEBEES_SPACE_H
