

#include "Game.h"
#include <typeinfo>

Game::Game(){
    int row_num = 0;
    // this array/linked list is kinda janky... when I have time I'll come back and make it a regular doubly-linked list.
    Space* next = nullptr;
    Space** Next_last = nullptr;
    for (int i = BOARD_LENGTH - 1; i >= 0; i--) {      // go in reverse so that we can set each 'next' pointer
        int coords[2] = {row_num, i};
        spaces[i] = new Space(coords);
        spaces[i]->setNext(next);       // set each 'next' pointer
        next = spaces[i];
    }

    for (int i = BOARD_LENGTH - 1; i >= 1; i--) {
        spaces[i]->setLast(spaces[i - 1]);
    }
}

Game::~Game() {

    for (int i = 0; i < BOARD_LENGTH; i++) {
        //delete spaces[i];
    }
}

void Game::game_loop() {

    Ant *newAnt = new Thrower(&spaces[BOARD_LENGTH - 2]);
    spaces[BOARD_LENGTH - 2].insertAnt(newAnt);
    do {
        // 1. Spawn new bee
        Bee *newBee = new BasicBee(&spaces[BOARD_LENGTH - 1]);
        spaces[BOARD_LENGTH - 1].insertBee(newBee);
        // 2. Allow player to place an ant
        //Ant *newAnt = new Thrower(spaces[BOARD_LENGTH - 2]);
        // Action Phase
        // 3. Ants act, beginning with leftmost ant
        for (int i = 0; i < BOARD_LENGTH; i++) {
            for (int j = 0; j < spaces[i].getAnts().size(); j++) {
                spaces[i].getAnts()[j]->act();
            }
        }
        // Actions include:
        //      - Harvester generating food
        //      - Throwers attacking
        //      -
        // 4. Bees act
        for (int i = BOARD_LENGTH - 1; i >= 0; i--) {
            for (int j = 0; j < spaces[i].getBees().size(); j++) {
                spaces[i].getBees()[j]->act();
            }
        }
        //      a) Move
        //   OR b) Attack
    } while (true);
}

void Game::insertUnit(Unit* unit, int position) {

    if (typeid(Ant) == typeid(unit)) {
        spaces[3]->insertAnt(dynamic_cast<Ant*>(unit));
    } else {    // typeid == Bee
        spaces[3]->insertBee(dynamic_cast<Bee*>(unit));
    }
}

