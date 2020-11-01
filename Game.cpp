

#include "Game.h"
#include <typeinfo>

Game::Game(){
    int row_num = 0;

    for (int i = 1; i < BOARD_LENGTH - 1; i++) {
        int coords[2] = {row_num, i};
        spaces[i] = new Space(coords);
        //spaces[i]->setNext(spaces[i + 1]);
    }
    // set each 'next' pointer
}

Game::~Game() {

    for (int i = 0; i < BOARD_LENGTH; i++) {
        delete spaces[i];
    }
}

void Game::game_loop() {

    // 1. Spawn new bee
    BasicBee *newBee = new BasicBee(spaces[BOARD_LENGTH - 1]);
    // 2. Allow player to place an ant
    // Action Phase
    // 3. Ants act, beginning with leftmost ant
    // Actions include:
    //      - Harvester generating food
    //      - Throwers attacking
    //      -
    // 4. Bees act
    //      a) Move
    //   OR b) Attack
}

void Game::insertUnit(Unit* unit, int position) {

    if (typeid(Ant) == typeid(unit)) {
        spaces[3]->insertAnt(dynamic_cast<Ant*>(unit));
    } else {    // typeid == Bee
        spaces[3]->insertBee(dynamic_cast<Bee*>(unit));
    }
}

