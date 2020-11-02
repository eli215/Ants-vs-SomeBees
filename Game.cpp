

#include "Game.h"
#include <typeinfo>
#include <iostream>
#include "Unit/Ant/Harvester.h"
#include "Unit/Ant/Thrower/Thrower.h"
#include "Unit/Ant/Thrower/ShortThrower.h"
#include "Unit/Ant/Thrower/LongThrower.h"
#include "Unit/Ant/Bodyguard.h"
#include "Unit/Ant/Wall.h"
#include "Unit/Ant/Ninja.h"
#include "Unit/Ant/Fire.h"

Game::Game() {
    this->numAnts = 0;
    this->numBees = 0;
}

Game::~Game() {

    for (int i = 0; i < BOARD_COLUMNS; i++) {
        //delete board[i];
    }
}

void Game::game_loop() {

    do {
        // 1. Spawn new bee
        spawnBee();
        //redrawBoard();
        // 2. Allow player to place an ant
        turnChoice();
        // Action Phase
        // 3. Ants act, beginning with leftmost ant
        for (int i = 0; i < BOARD_COLUMNS; i++) {
            for (int j = 0; j < board[i].getAnts().size(); j++) {
                board[i].getAnts()[j]->act();
            }
        }
        // Actions include:
        //      - Harvester generating food
        //      - Throwers attacking
        //      -
        // 4. Bees act
        for (int i = BOARD_COLUMNS - 1; i >= 0; i--) {
            for (int j = 0; j < board[i].getBees().size(); j++) {
                board[i].getBees()[j]->act();
            }
        }
        //      a) Move
        //   OR b) Attack
    } while (numBees > 0);

    // victory message
}

// insert a unit at the board coordinates specified: {rowInd, colInd}
void Game::insertUnit(Unit* unit, const int coordinates[2]) {
    int rowInd = coordinates[0];
    int colInd = coordinates[1];
    if (typeid(Ant) == typeid(unit)) {
        board[rowInd][colInd].insertAnt(dynamic_cast<Ant*>(unit));
    } else {    // typeid == Bee
        board[rowInd][colInd].insertBee(dynamic_cast<Bee*>(unit));
    }
}

void Game::spawnBee() {
    // if expanded to support multiple board rows, here is where we will randomly select
    // which rows to spawn bees in
    Bee* bee = new BasicBee();
    int spawnPoint[2] = {BOARD_ROWS - 1, BOARD_COLUMNS - 1};
    insertUnit(bee, spawnPoint);
}

void Game::turnChoice() {
    std::string input = "";
    int validInput = 0;

    std::cout << "What would you like to do?\n" <<
        "1. Place an Ant.\n" <<
        "2. Nothing.\n";

    do {
        std::cout << "Enter a number between 1 and 2: ";
        std::getline(std::cin, input);
        validInput = parseInput(input);
    } while (validInput < 1 || validInput > 2);

    if (validInput == 1) {
        selectAnt();
    }
}

void Game::selectAnt() {

}

// Parse string to int, returns INT_MAX if input contains invalid characters.
int Game::parseInput(const std::string& input) {
    int result;
    try {
        result = std::stoi(input);
        if (std::to_string(result).length() != input.length()) {    // check if any invalid chars were removed
            result = INT_MAX;
        }
    } catch (std::exception &e) {
        result = INT_MAX;
    }
    return result;
}

void Game::printAntTypes() {
    std::cout <<

    "1. " << typeid(Harvester).name() <<
    "2. " << typeid(Thrower).name() <<
    "3. " << typeid(ShortThrower).name() <<
    "4. " << typeid(LongThrower).name() <<
    "5. " << typeid(Bodyguard).name() <<
    "6. " << typeid(Wall).name() <<
    "7. " << typeid(Ninja).name() <<
    "8. " << typeid(Fire).name();
}

