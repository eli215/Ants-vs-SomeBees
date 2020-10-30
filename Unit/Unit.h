
#ifndef INC_5_UNIT_H
#define INC_5_UNIT_H

// abstract Unit class
class Unit {
protected:
    int armor;
    int maxArmor;

public:
    Unit();
    Unit(int armor, int maxArmor);
    //virtual ~Unit();
    //Unit(const Unit&);
    //Unit operator=(const Unit& u);

    virtual void act() = 0;     // pure virtual

    /* Getters & Setters */
    int getArmor() const;
    void setArmor(int);
    int getMaxArmor() const;
    void setMaxArmor(int);


};


#endif //INC_5_UNIT_H
