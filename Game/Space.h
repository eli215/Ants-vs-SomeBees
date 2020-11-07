
#ifndef ANTS_VS_SOMEBEES_SPACE_H
#define ANTS_VS_SOMEBEES_SPACE_H

#include <vector>
//#include "Unit/Ant/Ant.h"
//#include "Unit/Bee/Bee.h"
class Ant;
class Bee;

class Space {
protected:
    int coordinates[2];       //x coordinates cannot be changed after initialization
    std::vector<Ant*> ants;
    std::vector<Bee*> bees;
    bool blocked;

    Space *last;
    Space *next;
public:
    Space *getLast() const;
    void setLast(Space *last);
    Space *getNext();
    void setNext(Space *next);

    //Space(const int coords[2] = nullptr); // x
    Space();
    static void move(Bee* bee);

    /* Getters & Setters */
    const int *getCoordinates() const;

    std::vector<Ant *> &getAnts();
    void setAnts(const std::vector<Ant *> &ants);

    std::vector<Bee *> &getBees();
    void setBees(const std::vector<Bee *> &bees);

    bool isBlocked() const;
    void setBlocked(bool blocked);

    void insertAnt(Ant *ant);

    void insertBee(Bee *bee);
};


#endif //ANTS_VS_SOMEBEES_SPACE_H
