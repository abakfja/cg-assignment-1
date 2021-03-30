//
// Created by captain on 3/30/21.
//

#ifndef CG_ASSIGNMENT_GAME_H
#define CG_ASSIGNMENT_GAME_H

#include <player.h>
#include <board.h>
#include <items.h>
#include <vector>

class game {
public:
    player p;
    impostor im;
    board b;
    std::vector<wall> walls;

    game();

    void init();

    void draw(glm::mat4);

    void get_input(const int * keys);
};


#endif //CG_ASSIGNMENT_GAME_H
