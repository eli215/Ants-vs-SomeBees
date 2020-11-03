
#ifndef INC_5_UNIT_H
#define INC_5_UNIT_H

#include <string>
#include "../Game/Space.h"

// abstract Unit class
class Unit {
protected:
    std::string name;
    int armor;
    const int maxArmor;     // maxArmor cannot be changed after initialization
    Space* location;
    bool targetable;
    int actionPhase;

public:
    Unit();
    Unit(std::string name, int armor, int maxArmor, Space* location, bool targetable, int actionPhase);
    virtual ~Unit() = default;
    //Unit(const Unit&);
    //Unit operator=(const Unit& u);

    virtual void act() = 0;     // pure virtual
    bool isAlive() const;

    /* Getters & Setters */
    int getArmor() const;
    void setArmor(int);
    int getMaxArmor() const;
    Space *getLocation() const;
    void setLocation(Space *location);
    bool isTargetable() const;
    void setTargetable(bool targetable);

    int getActionPhase() const;

    void setActionPhase(int actionPhase);

    const std::string &getName() const;

    void setName(const std::string &name);

};


#endif //INC_5_UNIT_H
