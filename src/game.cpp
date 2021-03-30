//
// Created by captain on 3/30/21.
//

#include "game.h"

game::game() :
        b{glm::vec2{0, 0}, 5.0f, 5.0f},
        p{glm::vec2{0, 0}, 0.1f},
        im{glm::vec2{0, 0}, 0.1f} {
}


void game::init() {

}

void game::draw(glm::mat4 VP) {
    b.draw(VP);
    im.draw(VP);
    p.draw(VP);
}

void game::get_input(const int *keys) {
    if (keys[0]) { // left
        p.position.x -= p.speed;
    }
    if (keys[1]) { // right
        p.position.x += p.speed;
    }
    if (keys[2]) { // up
        p.position.y += p.speed;
    }
    if (keys[3]) { // down
        p.position.y -= p.speed;
    }
}
