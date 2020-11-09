

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
        board[row][i].setCoordinates(row, i);       // set coordinates
    }
    board[row][BOARD_COLUMNS - 1].setCoordinates(row, BOARD_COLUMNS - 1);   // set last coord

    for (int i = BOARD_COLUMNS - 1; i > 0; i--) {       // reverse iteration
        board[row][i].setLast(&board[row][i - 1]);  // set 'last' pointer
    }
}

Game::~Game() {
    // Space destructor will handle deletion of all the allocated Units
}

void Game::game_loop() {

    int turnCount = 1;
    const int row = 0;      // since the game only supports one row currently

    do {
        std::cout << "\n\n[Turn #" << turnCount++ << "]********************************************************************"
                                                     "*********************************************************************"
                                                     "***************\n\n\n";

        // SPAWN NEW BEE & REDRAW BOARD
        spawnBee();
        std::cout << "FOOD BANK: " << foodBank << "\n";
        redrawBoard();
        std::cout << "The Hive spawned a new Bee.\n\n";

        // PLAYER TURN CHOICE
        turnChoice();

        // ACTION PHASE 1 - Ants act
        bool havePhase3 = false;
        for (int col = 1; col < BOARD_COLUMNS; col++) {
            Space* space = &board[row][col];
            // for each Ant in this space
            int size = space->getAnts().size();
            for (int i = 0; i < size; i++) {
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
            int size = space->getBees().size();
            for (int i = 0; i < size; i++) {
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
                    space->setUnitCount(space->getUnitCount() - 1); // decrement unitCount
                    numAnts--;
                }
            }
            // for each Bee in this space
            for (int i = 0; i < space->getBees().size(); i++) {
                Bee* bee = space->getBees()[i];
                if (!bee->isAlive()) {
                    space->getBees().erase(space->getBees().begin() + i);   // remove the dead Bee
                    space->setUnitCount(space->getUnitCount() - 1); // decrement unitCount
                    numBees--;
                }
            }
        }

    } while (numBees > 0 && board[0][0].getBees().empty());

    if (numBees < 1)
        std::cout << "\n\nCONGRATULATIONS, YOU WIN!!! THE BEES HAVE BEEN DEFEATED.\n";
    else
        std::cout << "\n\nYou have failed to protect the Queen. You lose. :(\n:(\n:(\n:(\n:(";
    std::cin.ignore();
}

// Spawn a BasicBee
void Game::spawnBee() {
    // if expanded to support multiple board rows, here is where we will randomly select
    // which rows to spawn bees in
    //int coordinates[2] = {BOARD_ROWS - 1, BOARD_COLUMNS - 1};
    Space *spawnPoint = &board[0][BOARD_COLUMNS - 1];
    Bee* bee = new BasicBee(spawnPoint);
    insertBee(bee);
}

// Draw the board
void Game::redrawBoard() {
    // Possible space types
    // 0 - blank space
    // 1 - ant space
    // 2 - bee space
    // 3 - ant & bee space
    // 4 - queen ant
    // 5 - beehive
    int row = 0;
    int colSpaceType[BOARD_COLUMNS];
    for (int i = 0; i < BOARD_COLUMNS; i++) {
        if (i == 0)
            colSpaceType[i] = 4;               // Queen Ant
        else if (!board[row][i].getAnts().empty()) {
            if (!board[row][i].getBees().empty())
                colSpaceType[i] = 3;           // Ants & Bees
            else
                colSpaceType[i] = 1;           // Ants only
        } else if (!board[row][i].getBees().empty())
            colSpaceType[i] = 2;               // Bees only
        else
            colSpaceType[i] = 0;               // Blank
    }

    int linesPerSpace = Graphics::BLANK.size();
    std::vector<std::vector<std::string>> spaceArt;
    spaceArt.push_back(Graphics::BLANK);
    spaceArt.push_back(Graphics::ANT);
    spaceArt.push_back(Graphics::BEE);
    spaceArt.push_back(Graphics::ANT_AND_BEE);
    spaceArt.push_back(Graphics::QUEEN_ANT);
    spaceArt.push_back(Graphics::BEE_HIVE);

    // PRINT TOP BORDER
    std::cout << "+";
    for (int i = 0; i < BOARD_COLUMNS; i++)
        std::cout << "---------------+";
    std::cout << "\n";
    // PRINT GRAPHICS
    for (int line = 0; line < linesPerSpace - 1; line++) {
        std::cout << "|";
        for (int col = 0; col < BOARD_COLUMNS; col++) {
            std::cout << spaceArt[colSpaceType[col]][line] << "|";
        }
        std::cout << spaceArt[5][line];     // print bee hive
        std::cout << "\n";
    }

    // PRINT UNIT COUNT for each square that isn't blank
    std::cout << "|";
    std::string str1;
    std::string str2;
    str1.resize(16);
    str2.resize(16);

    for (int col = 0, lineIdx = 5; col < BOARD_COLUMNS; col++) {
        int type = colSpaceType[col];
        int size1, size2;
        if (type == 4)      // Queen Ant has no unit count
            str1 = spaceArt[type][lineIdx];
        if (type == 0)
            str1 = spaceArt[type][lineIdx];
        else if (type == 3) {
            size1 = board[row][col].getAnts().size();
            size2 = board[row][col].getBees().size();
            sprintf(&str1[0], spaceArt[type][lineIdx].c_str(), size1, size2);
        } else {
            if (type == 1)
                size1 = board[row][col].getAnts().size();
            else
                size1 = board[row][col].getBees().size();
            sprintf(&str1[0], spaceArt[type][lineIdx].c_str(), size1);
        }
        std::cout << str1 << "|";
    }
    std::cout << spaceArt[5][5];     // print last line of beehive

    //str.resize( strlen( str.data() ) + 1 );
    std::cout << "\n";

    // PRINT BOTTOM BORDER
    std::cout << "+";
    for (int i = 0; i < BOARD_COLUMNS; i++)
        std::cout << "---------------+";
    std::cout << "\n";

    // PRINT SPACE NUMBER LABEL
    std::cout << "|";
    for (int i = 0; i < BOARD_COLUMNS; i++) {
        sprintf(&str1[0], "%5s[%-2d]%6s", " ", i + 1, " ");
        std::cout << str1 << "|";
    }
    std::cout << "\n";

    // PRINT ANOTHER BORDER
    std::cout << "|";
    for (int i = 0; i < BOARD_COLUMNS; i++)
        std::cout << "---------------|";
    std::cout << "\n";

    // PRINT UNIT LIST BELOW EACH SPACE
    int maxSpaceAnts = 1;
    int maxSpaceBees = 0;
    for (int i = 0; i < BOARD_COLUMNS; i++) {
        maxSpaceAnts = std::max(maxSpaceAnts, (int)board[row][i].getAnts().size());
        maxSpaceBees = std::max(maxSpaceBees, (int)board[row][i].getBees().size());
    }
    maxSpaceAnts = std::min(maxSpaceAnts, 2);     // max 2 lines for ants
    maxSpaceBees = std::min(maxSpaceBees, 4);     // max 4 lines for bees

    // FIRST PRINT ANT LIST
    //if (numAnts > 0) {
        for (int line = 0; line < maxSpaceAnts; line++) {
            std::cout << "|";
            for (int col = 0; col < BOARD_COLUMNS; col++) {
                if (col == 0)
                    str2 = "   Queen Ant   ";
                else if (board[row][col].getAnts().size() > line) {
                    Ant *ant = board[row][col].getAnts()[line];
                    sprintf(&str1[0], "%s(%d/%d)", ant->getAbbrev().c_str(), ant->getArmor(), ant->getMaxArmor());
                    sprintf(&str2[0], "%-15s", str1.c_str());
                } else{
                    str2 = "               ";       // blank this column has no more bees to print
                }
                std::cout << str2 << "|";
            }
            std::cout << "\n";
        }
        // print border line
        std::cout << "|";
        for (int i = 0; i < BOARD_COLUMNS; i++)
            std::cout << "---------------|";
        std::cout << "\n";
    //}

    // THEN PRINT BEE LIST (first 3 bees; 4th line will be ellipses)
    if (numBees > 0) {
        for (int line = 0; line < maxSpaceBees; line++) {
            std::cout << "|";
            for (int col = 0; col < BOARD_COLUMNS; col++) {
                if (board[row][col].getBees().size() > line) {
                    Bee *bee = board[row][col].getBees()[line];
                    if (line == 3)
                        sprintf(&str1[0], "...x%-2d", board[row][col].getBees().size() - 3);
                    else
                        sprintf(&str1[0], "~%s(%d/%d)", bee->getAbbrev().c_str(), bee->getArmor(), bee->getMaxArmor());
                    sprintf(&str2[0], "%15s", str1.c_str());
                } else{
                    str2 = "               ";       // blank this column has no more bees to print
                }
                std::cout << str2 << "|";
            }
            std::cout << "\n";
        }
        // print border line
        std::cout << "|";
        for (int i = 0; i < BOARD_COLUMNS; i++)
            std::cout << "---------------|";
        std::cout << "\n";
    }
}

void Game::turnChoice() {
    std::string input = "";
    int validInput = 0;
    bool repeatTurn = false;

    do {
        repeatTurn = false;
        std::cout << "\nWhat would you like to do?\n" <<
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
                coords = selectLocation();      // [0] = row, [1] = col
                Space* location = &board[coords[0]][coords[1]];     // get the Space at the user's coordinates
                if(!selectAnt(&ant, location)) {       // if user chose to cancel
                    repeatTurn = true;
                    break;
                }

            } while (!canPlace(ant, coords));
            if (!repeatTurn) {
                insertAnt(ant, coords);
                std::cout << "\n***** [Action Log] *****\n";
                std::cout << "You placed a " << ant->getName() << " in space [" << coords[1] + 1 << "].\n";
            }
        } else {
            std::cout << "\n***** [Action Log] *****\n";
            std::cout << "You skipped your turn.\n";
        }
    } while (repeatTurn);
}

int *Game::selectLocation() {
    std::string input = "";
    int validInput = 0;
    int *coords = new int(2);   //{row, column};

    // if we had more than one row, we'd select the row first-- eg. std::cout << "Select a row # between 1 and " << BOARD_ROWS + 1 << ": \n";
    coords[0] = 0;  // ROW INDEX
    std::cout << "\nWhere do you want to place it?\n";

    do {
        std::cout << "Select a column # between 2 and " << BOARD_COLUMNS << ": ";
        std::getline(std::cin, input);
        validInput = parseInput(input);
    } while (validInput < 2 || validInput > BOARD_COLUMNS);
    coords[1] = validInput - 1;     // COLUMN INDEX

    return coords;
}

bool Game::selectAnt(Ant** selection, Space* location) {
    std::string input = "";
    int validInput = 0;
    bool repeat = false;
    bool canceled = false;

    std::cout << "\nFOOD BANK: " << foodBank << "\n\n";
    printAntTypes();
    std::cout << "9. Cancel.\n";
    std::cout << "\nWhich Ant do you want to place?\n";

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

void Game::printAntTypes() {
    // TO-DO: Make this print out a nice looking table with
    // Name | Food Cost | Armor | Damage | Brief Description
    // std::cout << "\u221E"; unicode infinity symbol? for fire ant
    // Count the exact number of characters in this table, and cout backspaces to
    // delete the table after each time it prints?
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
    numAnts++;
    foodBank -= ant->getFoodCost();
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
    numBees++;
}

bool Game::canPlace(Ant* ant, int *coords) {
    int row = coords[0];
    int col = coords[1];
    Space *space = ant->getLocation();
    bool isBG = typeid(*ant) ==  typeid(Bodyguard);
    bool isWall = typeid(*ant) ==  typeid(Wall);
    bool spaceHasBG = false;
    bool spaceHasWall = false;
    if (space->getAnts().size() == 1) {
        spaceHasBG = (typeid(*space->getAnts()[0]) == typeid(Bodyguard));
        spaceHasWall = (typeid(*space->getAnts()[0]) == typeid(Wall));
    }
    bool canPlace = false;

    if (ant->getFoodCost() > foodBank)
        std::cout << "Insufficient food; you can't place a " << ant->getName() << ".\n";
    else if (board[row][col].getAnts().empty() ||
                board[row][col].getAnts().size() == 1
                && ((!spaceHasWall) && (!isWall) && (spaceHasBG /*XOR*/!= isBG)))
         {
        canPlace = true;
    } else
       std::cout << "Space occupied; you can't place a " << ant->getName() << " here.\n";

    return canPlace;
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
