
#ifndef ANTS_VS_SOME_BEES_WALL_H
#define ANTS_VS_SOME_BEES_WALL_H


#include "Ant.h"

class Wall : public Ant {
    public:
    Wall(Space* location = nullptr);
    void act() override;

    static const std::string BASE_NAME;     // = "Wall"
    static const std::string BASE_ABBREV;
    static const int BASE_FOOD_COST = 4;
    static const int BASE_MAX_ARMOR = 4;
    static const int BASE_TARGETABILITY = true;
    static const int BASE_ACTION_PHASE = 1;

};


#endif //ANTS_VS_SOME_BEES_WALL_H
