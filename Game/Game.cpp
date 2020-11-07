

#include "Game.h"
#include <typeinfo>
#include <iostream>
#include "Graphics.h"
#include <string>
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
    this->foodBank = STARTING_FOOD;

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

    int turnCount = 1;
    const int row = 0;      // since the game only supports one row currently

    redrawBoard();      // draw a blank board for user to reference on their first turn
    do {
        std::cout << "[Turn #" << turnCount++ << "]=============================================================================================\n";
        // PLAYER TURN CHOICE
        turnChoice();

        // SPAWN NEW BEE & REDRAW BOARD
        spawnBee();
        redrawBoard();
        std::cout << "Turn log: \n";
        std::cout << "The Hive spawns a new Bee.\n";

        // ACTION PHASE 1 - Ants act
        bool havePhase3 = false;
        for (int col = 1; col < BOARD_COLUMNS; col++) {
            Space* space = &board[row][col];
            // for each Ant in this space
            int s = space->getAnts().size();
            for (int i = 0; i < space->getAnts().size(); i++) {
                Ant* ant = space->getAnts()[i];
                if (ant->getActionPhase() == 3) {
                    havePhase3 = true;
                    continue;
                } else {
                    ant->act();
                    if (typeid(ant) == typeid(Harvester))
                        foodBank += Harvester::BASE_FOOD_PRODUCTION;
                }
            }
        }

        // ACTION PHASE 2 - Bees act
        for (int col = 0; col < BOARD_COLUMNS; col++) {
            Space* space = &board[row][col];
            // for each Bee in this space
            for (int i = 0; i < space->getBees().size(); i++) {
                BasicBee* bBee = dynamic_cast<BasicBee*>(space->getBees()[i]);      // for now, we are assuming all Bees are BasicBees
                if (bBee->enemyInRange())
                    bBee->act();            // if possible, attack an Ant in range
                else
                    Space::move(bBee);      // otherwise, advance to the next Space
            }
        }

        // ACTION PHASE 3 - Ants with special abilities act
        for (int col = 0; havePhase3 && col < BOARD_COLUMNS; col++) {
            Space* space = &board[row][col];
            // for each Ant in this space
            for (int i = 0; i < space->getAnts().size(); i++) {
                Ant* ant = space->getAnts()[i];
                if (ant->getActionPhase() == 3) {
                    ant->act();
                }
            }
        }

        // CLEAN-UP PHASE - Remove the bodies of fallen Units
        for (int col = 0; col < BOARD_COLUMNS; col++) {
            Space* space = &board[row][col];
            // for each Ant in this space
            for (int i = 0; i < space->getAnts().size(); i++) {
                Ant* ant = space->getAnts()[i];
                if (!ant->isAlive()) {
                    space->getAnts().erase(space->getAnts().begin() + i);   // remove the dead Ant
                    numAnts--;
                }
            }
            // for each Bee in this space
            for (int i = 0; i < space->getBees().size(); i++) {
                Bee* bee = space->getBees()[i];
                if (!bee->isAlive()) {
                    space->getBees().erase(space->getBees().begin() + i);   // remove the dead Ant
                    numAnts--;
                }
            }
        }

    } while (numBees > 0 && board[0][0].getBees().empty());

    // victory message
}

void Game::redrawBoard() {
    // 0 - blank space
    // 1 - ant space
    // 2 - bee space
    // 3 - ant & bee space
    int row = 0;
    int spaceTypeIdx[BOARD_COLUMNS];
    for (int i = 0; i < BOARD_COLUMNS; i++) {
        if (!board[row][i].getAnts().empty()) {
            if (!board[row][i].getBees().empty())
                spaceTypeIdx[i] = 3;           // Ants & Bees
            else
                spaceTypeIdx[i] = 1;           // Ants only
        } else if (!board[row][i].getBees().empty())
            spaceTypeIdx[i] = 2;               // Bees only
        else
            spaceTypeIdx[i] = 0;               // Blank
    }

    int linesPerSpace = Graphics::BLANK.size();
    std::vector<std::vector<std::string>> spaceType;
    spaceType.push_back(Graphics::BLANK);
    spaceType.push_back(Graphics::ANT);
    spaceType.push_back(Graphics::BEE);
    spaceType.push_back(Graphics::ANT_AND_BEE);

    std::cout << "+";
    for (int i = 0; i < BOARD_COLUMNS; i++)
        std::cout << "---------------+";
    std::cout << "\n";

    for (int line = 0; line < linesPerSpace - 1; line++) {
        std::cout << "|";
        for (int col = 0; col < BOARD_COLUMNS; col++) {
            //sprintf(&str[0], )
            std::cout << spaceType[spaceTypeIdx[col]][line] << "|";
        }
        std::cout << "\n";
    }

    // print unit count for each square that isn't blank
    std::cout << "|";
    std::string str;
    str.resize(16);

    for (int col = 0, lineIdx = 5; col < BOARD_COLUMNS; col++) {
        int type = spaceTypeIdx[col];
        int size1, size2;

        if (type == 1)
            size1 = board[row][col].getAnts().size();
        else if (type == 2)
            size1 = board[row][col].getBees().size();
        else if (type == 3) {
            size1 = board[row][col].getAnts().size();
            size2 = board[row][col].getBees().size();
        }

        if (type == 0)
            str = spaceType[type][lineIdx];
        else if (type == 3)
            sprintf( &str[0], spaceType[type][lineIdx].c_str(), size1, size2);
        else
            sprintf( &str[0], spaceType[type][lineIdx].c_str(), size1);

        std::cout << str << "|";
    }
    //str.resize( strlen( str.data() ) + 1 );
    std::cout << "\n";

    std::cout << "+---------------+---------------+---------------+---------------+---------------+---------------+---------------+---------------+---------------+---------------+\n";

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
    //int coordinates[2] = {BOARD_ROWS - 1, BOARD_COLUMNS - 1};
    Space *spawnPoint = &board[0][BOARD_COLUMNS - 1];
    Bee* bee = new BasicBee(spawnPoint);
    insertBee(bee);
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
                if(!selectAnt(&ant, location)) {       // if user chose to cancel
                    repeatTurn = true;
                    break;
                }

            } while (!canPlace(ant, coords));
            if (!repeatTurn)
                insertAnt(ant, coords);
        }
    } while (repeatTurn);
}



bool Game::selectAnt(Ant** selection, Space* location) {
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
                else        *selection = new Harvester(location);
                break;
            case 2:
                if (Thrower::BASE_FOOD_COST > foodBank)    repeat = true;
                else        *selection = new Thrower(location);
                break;
            case 3:
                if (ShortThrower::BASE_FOOD_COST > foodBank)    repeat = true;
                else        *selection = new ShortThrower(location);
                break;
            case 4:
                if (LongThrower::BASE_FOOD_COST > foodBank)    repeat = true;
                else        *selection = new LongThrower(location);
                break;
            case 5:
                if (Bodyguard::BASE_FOOD_COST > foodBank)    repeat = true;
                else        *selection = new Bodyguard(location);
                break;
            case 6:
                if (Wall::BASE_FOOD_COST > foodBank)    repeat = true;
                else        *selection = new Wall(location);
                break;
            case 7:
                if (Ninja::BASE_FOOD_COST > foodBank)    repeat = true;
                else        *selection = new Ninja(location);
                break;
            case 8:
                if (Fire::BASE_FOOD_COST > foodBank)    repeat = true;
                else        *selection = new Fire(location);
                break;
            case 9:
                canceled = true;
            default:
                *selection = nullptr;
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

    // if we had more than one row, we'd select the row first-- eg. std::cout << "Select a row # between 1 and " << BOARD_ROWS + 1 << ": \n";
    coords[0] = 0;  // ROW INDEX

    do {
        std::cout << "Select a column # between 2 and " << BOARD_COLUMNS << ": \n";
        std::getline(std::cin, input);
        validInput = parseInput(input);
    } while (validInput < 2 || validInput > BOARD_COLUMNS);
    coords[1] = validInput - 1;     // COLUMN INDEX

    return coords;
}


void Game::printAntTypes() {
    std::cout <<
              "1. " << Harvester::BASE_NAME << '\n' <<
              "2. " << Thrower::BASE_NAME << '\n' <<
              "3. " << ShortThrower::BASE_NAME << '\n' <<
              "4. " << LongThrower::BASE_NAME << '\n' <<
              "5. " << Bodyguard::BASE_NAME << '\n' <<
              "6. " << Wall::BASE_NAME << '\n' <<
              "7. " << Ninja::BASE_NAME << '\n' <<
              "8. " << Fire::BASE_NAME << '\n';
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
   if (board[row][col].getAnts().empty() ||
        (board[row][col].getAnts().size() == 1 && typeid(board[row][col].getAnts()[0]) != typeid(Bodyguard)
        && typeid(ant) ==  typeid(Bodyguard))) {
        return true;
    } else {
       std::cout << "Space occupied; you can't place a " << ant->getName() << " here.\n";
       return false;
   }
}


