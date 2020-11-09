
#ifndef ANTS_VS_SOMEBEES_SPACE_H
#define ANTS_VS_SOMEBEES_SPACE_H

#include <vector>
//#include "Unit/Ant/Ant.h"
//#include "Unit/Bee/Bee.h"
class Ant;
class Bee;

class Space {
protected:
    int coordinates[2];
    std::vector<Ant*> ants;
    std::vector<Bee*> bees;
    int unitCount;
    //bool blocked;

    Space *last;
    Space *next;
public:
    Space();
    //Space(const int coords[2] = nullptr);
    ~Space();
    static void move(Bee* bee);
    void insertAnt(Ant *ant);
    void insertBee(Bee *bee);

    /* Getters & Setters */
    Space *getLast() const;
    void setLast(Space *last);

    Space *getNext();
    void setNext(Space *next);

    const int *getCoordinates() const;
    void setCoordinates(int row, int col);

    int getRow() const;
    int getCol() const;

    std::vector<Ant *> &getAnts();
    void setAnts(const std::vector<Ant *> &ants);

    std::vector<Bee *> &getBees();
    void setBees(const std::vector<Bee *> &bees);

    //bool isBlocked() const;
    //void setBlocked(bool blocked);

    int getUnitCount() const;
    void setUnitCount(int unitCount);
};


#endif //ANTS_VS_SOMEBEES_SPACE_H
