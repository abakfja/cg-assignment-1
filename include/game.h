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
    maze m;
    const int row, col;
    static constexpr int w = 6, h = 6;

    game(int r, int c);

    void init();

    void draw2d(glm::mat4) const;
    void draw3d(glm::mat4) const;

    void get_input(const int *keys);
};


#endif //CG_ASSIGNMENT_GAME_H
