
#ifndef INC_5_GAME_H
#define INC_5_GAME_H

#include <vector>
#include <string>
#include "Space.h"
#include "Unit/Unit.h"
#include "Unit/Ant/Ant.h"
#include "Unit/Bee/BasicBee.h"
#include "Unit/Ant/Thrower/Thrower.h"

class Game {
public:
    Game();
    ~Game();
    //Game(const Game&);
    //Game operator=(const Game& g);
    static const int BOARD_ROWS = 1;
    static const int BOARD_COLUMNS = 10;

    void game_loop();

protected:
    Space board[BOARD_ROWS][BOARD_COLUMNS];
    int numBees;
    int numAnts;

    void insertUnit(Unit *unit, const int coordinates[2]);

    void spawnBee();

    void turnChoice();

    int parseInput(const std::string& input);

    void selectAnt();

    void printAntTypes();
};


#endif //INC_5_GAME_H
