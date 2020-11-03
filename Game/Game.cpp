

#include "Game.h"
#include <typeinfo>
#include <iostream>
#include "../Unit/Ant/Harvester.h"
#include "../Unit/Ant/Thrower/Thrower.h"
#include "../Unit/Ant/Thrower/ShortThrower.h"
#include "../Unit/Ant/Thrower/LongThrower.h"
#include "../Unit/Ant/Bodyguard.h"
#include "../Unit/Ant/Wall.h"
#include "../Unit/Ant/Ninja.h"
#include "../Unit/Ant/Fire.h"

Game::Game() {
    this->numAnts = 0;
    this->numBees = 0;

    // it may be kind of janky that 'board' is both an array and a doubly-linked list, but for now it does the job.
    int row = 0;
    for (int i = 0; i < BOARD_COLUMNS - 1; i++) {       // forward iteration
        board[row][i].setNext(&board[row][i + 1]);  // set 'next' pointer
    }

    for (int i = BOARD_COLUMNS - 1; i > 0; i--) {       // reverse iteration
        board[row][i].setLast(&board[row][i - 1]);  // set 'last' pointer
    }
}

Game::~Game() {

    for (int i = 0; i < BOARD_COLUMNS; i++) {
        //delete board[i];
    }
}

void Game::game_loop() {

    do {
        // 1. Spawn new bee
        std::cout << "+---------------+---------------+---------------+---------------+---------------+---------------+---------------+---------------+---------------+---------------+";
        spawnBee();
        //redrawBoard();
        // 2. Allow player to place an ant
        turnChoice();

        // Action Phase
        std::cout << "Combat log: \n";
        // 3. Ants act, beginning with leftmost ant
        //for (int i = 0; i < BOARD_ROWS; i++) {
        int row = 0;
        for (int col = 1; col < BOARD_COLUMNS; col++) {
            // for each Ant in this space
            for (int i = 0; i < board[row][col].getAnts().size(); i++) {
                board[row][col].getAnts()[i]->act();
            }
        }
        // Actions include:
        //      - Harvester generating food
        //      - Throwers attacking
        //      -
        // 4. Bees act
        for (int i = BOARD_COLUMNS - 1; i >= 0; i--) {
            //for (int j = 0; j < board[i].getBees().size(); j++) {
                //board[i].getBees()[j]->act();
            //}
        }
        //      a) Move
        //   OR b) Attack
    } while (numBees > 0);

    // victory message
}

void Game::redrawBoard() {

    std::string str;
    str.resize(100);
    //std::string

    std::cout << "+----------+----------+----------+----------+----------+----------+----------+----------+----------+----------+\n";

}


// insert a unit at the board (at coordinates, if specified: {rowInd, colInd})
void Game::insertAnt(Ant* ant, int coordinates[2]) {
    Space* space;
    if (coordinates) {
        int rowInd = coordinates[0];
        int colInd = coordinates[1];
        space = &board[rowInd][colInd];
    } else {
        space = ant->getLocation();
    }
    space->insertAnt(ant);
}

// insert a unit at the board (at coordinates, if specified: {rowInd, colInd})
void Game::insertBee(Bee* bee, int coordinates[2]) {
    Space* space;
    if (coordinates) {
        int rowInd = coordinates[0];
        int colInd = coordinates[1];
        space = &board[rowInd][colInd];
    } else {
        space = bee->getLocation();
    }
    space->insertBee(bee);
}

void Game::spawnBee() {
    // if expanded to support multiple board rows, here is where we will randomly select
    // which rows to spawn bees in
    Bee* bee = new BasicBee();
    int spawnPoint[2] = {BOARD_ROWS - 1, BOARD_COLUMNS - 1};
    insertBee(bee, spawnPoint);
    numBees++;
}

void Game::turnChoice() {
    std::string input = "";
    int validInput = 0;
    bool repeatTurn = false;

    do {
        repeatTurn = false;
        std::cout << "What would you like to do?\n" <<
                  "1. Place an Ant.\n" <<
                  "2. Nothing.\n";
        do {
            std::cout << "Enter a number between 1 and 2: ";
            std::getline(std::cin, input);
            validInput = parseInput(input);
        } while (validInput < 1 || validInput > 2);

        if (validInput == 1) {
            Ant *ant;
            int *coords;
            do {
                coords = selectLocation();
                Space* location = &board[coords[0]][coords[1]];     // get the Space at the user's coordinates
                if(!selectAnt(ant, location)) {       // if user chose to cancel
                    repeatTurn = true;
                    break;
                }

            } while (!canPlace(ant, coords));
            if (!repeatTurn)
                insertAnt(ant, coords);
        }
    } while (repeatTurn);
}



bool Game::selectAnt(Ant* selection, Space* location) {
    std::string input = "";
    int validInput = 0;
    bool repeat = false;
    bool canceled = false;

    printAntTypes();
    std::cout << "9. Cancel.\n";

    do {
        repeat = false;
        do {
            std::cout << "Enter a number between 1 and 9: ";
            std::getline(std::cin, input);
            validInput = parseInput(input);
        } while (validInput < 1 || validInput > 9);

        // check that we have enough food for this choice
        switch (validInput) {
            case 1:
                if (Harvester::BASE_FOOD_COST > foodBank)    repeat = true;
                else        selection = new Harvester(location);
                break;
            case 2:
                if (Thrower::BASE_FOOD_COST > foodBank)    repeat = true;
                else        selection = new Thrower(location);
                break;
            case 3:
                if (ShortThrower::BASE_FOOD_COST > foodBank)    repeat = true;
                else        selection = new ShortThrower(location);
                break;
            case 4:
                if (LongThrower::BASE_FOOD_COST > foodBank)    repeat = true;
                else        selection = new LongThrower(location);
                break;
            case 5:
                if (Bodyguard::BASE_FOOD_COST > foodBank)    repeat = true;
                else        selection = new Bodyguard(location);
                break;
            case 6:
                if (Wall::BASE_FOOD_COST > foodBank)    repeat = true;
                else        selection = new Wall(location);
                break;
            case 7:
                if (Ninja::BASE_FOOD_COST > foodBank)    repeat = true;
                else        selection = new Ninja(location);
                break;
            case 8:
                if (Fire::BASE_FOOD_COST > foodBank)    repeat = true;
                else        selection = new Fire(location);
                break;
            case 9:
                canceled = true;
            default:
                selection = nullptr;
                break;
        }

        if (repeat) {
            std::cout << "Insufficient food place this Ant. Choose a different one.\n";
        }
    } while (repeat);

    return !canceled;
}

int *Game::selectLocation() {
    std::string input = "";
    int validInput = 0;
    int *coords = new int(2);   //{row, column};

    // if we had more than one row, we'd select the row first
    //std::cout << "Select a row # between 1 and " << BOARD_ROWS + 1 << ": \n";
    coords[0] = 0;  // ROW INDEX

    do {
        std::cout << "Select a column # between 2 and " << BOARD_COLUMNS + 1 << ": \n";
        std::getline(std::cin, input);
        validInput = parseInput(input);
    } while (validInput < 2 || validInput > BOARD_COLUMNS);
    coords[1] = validInput - 1;     // COLUMN INDEX

    return coords;
}


void Game::printAntTypes() {
    std::cout <<
              "1. " << typeid(Harvester).name() << '\n' <<
              "2. " << typeid(Thrower).name() << '\n' <<
              "3. " << typeid(ShortThrower).name() << '\n' <<
              "4. " << typeid(LongThrower).name() << '\n' <<
              "5. " << typeid(Bodyguard).name() << '\n' <<
              "6. " << typeid(Wall).name() << '\n' <<
              "7. " << typeid(Ninja).name() << '\n' <<
              "8. " << typeid(Fire).name() << '\n';
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

bool Game::canPlace(Ant* ant, int *coords) {
    int row = coords[0];
    int col = coords[1];

    // If space is uninhabited OR If space contains one non-Bodyguard and incoming Ant IS a Bodyguard
   if (board[row][col].getAnts().size() == 0 ||
        (board[row][col].getAnts().size() == 1 && typeid(board[row][col].getAnts()[0]) != typeid(Bodyguard)
        && typeid(ant) ==  typeid(Bodyguard))) {
        return true;
    } else {
       std::cout << "Space occupied; you can't place a " << typeid(ant).name() << "here.\n";
       return false;
   }
}


