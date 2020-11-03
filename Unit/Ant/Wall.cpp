
#include "Wall.h"

Wall::Wall(Space *location)
: Ant(BASE_MAX_ARMOR,BASE_MAX_ARMOR, location, BASE_TARGETABILITY,BASE_FOOD_COST, BASE_ACTION_PHASE) {

}

void Wall::act() {
    //Ant::act();
}
