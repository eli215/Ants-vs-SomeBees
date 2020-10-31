
#ifndef INC_5_GAME_H
#define INC_5_GAME_H

#include <vector>
#include "Space.h"

class Game {
protected:
    std::vector<Space> spaces;

public:
    Game();
    ~Game();
    //Game(const Game&);
    //Game operator=(const Game& g);

    void game_loop();

};


#endif //INC_5_GAME_H
