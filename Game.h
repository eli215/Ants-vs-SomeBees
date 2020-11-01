
#ifndef INC_5_GAME_H
#define INC_5_GAME_H

#include <vector>
#include "Space.h"
#include "Unit/Unit.h"
#include "Unit/Ant/Ant.h"
#include "Unit/Bee/BasicBee.h"

class Game {
public:
    Game();
    ~Game();
    //Game(const Game&);
    //Game operator=(const Game& g);
    static const int BOARD_LENGTH = 10;

    void game_loop();

protected:
    //std::vector<Space> spaces;
    Space *spaces[BOARD_LENGTH];

    void insertUnit(Unit *unit, int position);
};


#endif //INC_5_GAME_H
