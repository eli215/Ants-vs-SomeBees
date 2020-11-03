
#ifndef ANTS_VS_SOMEBEES_GAME_H
#define ANTS_VS_SOMEBEES_GAME_H

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



    static constexpr Ant* ANT_TYPES[8] = {

    };

protected:
    Space board[BOARD_ROWS][BOARD_COLUMNS];
    int foodBank;
    int numBees;
    int numAnts;

    void spawnBee();

    void turnChoice();

    int parseInput(const std::string& input);

    bool selectAnt(Ant*, Space*);
    int* selectLocation();

    void printAntTypes();

    bool canPlace(Ant* ant, int *coords);

    void redrawBoard();

    void insertAnt(Ant *ant, int coordinates[2] = nullptr);     // optional coords
    void insertBee(Bee *bee, int coordinates[2] = nullptr);     // optional coords
};


#endif //ANTS_VS_SOMEBEES_GAME_H
