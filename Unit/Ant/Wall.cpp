
#include "Wall.h"

const std::string Wall::BASE_NAME("Wall");
const std::string Wall::BASE_ABBREV("Wall");

Wall::Wall(Space *location)
: Ant(BASE_NAME, BASE_ABBREV, BASE_MAX_ARMOR,BASE_MAX_ARMOR, location, BASE_TARGETABILITY,BASE_FOOD_COST, BASE_ACTION_PHASE) {

}

void Wall::act() {
    //Ant::act();
}
