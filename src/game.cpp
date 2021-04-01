//
// Created by captain on 3/30/21.
//

#include "game.h"

game::game(int r, int c) : row{r}, col{c} {
}


void game::init() {
    // create the maze before init it

    b = board{glm::vec2{0, 0}, static_cast<float>(row * w), static_cast<float>(col * h)};

    m = maze(2.0f);
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            m.add_wall(wall(glm::vec2(i * w, j * h), glm::vec2((i + 1) * w, j * h)));
            m.add_wall(wall(glm::vec2(i * w, j * h), glm::vec2(i * w, (j + 1) * h)));
        }
    }

    m.init();
    p = player{glm::vec2{0, 0}, 0.1f};
    im = impostor{glm::vec2{0, 0}, 0.1f};

}


void game::draw2d(glm::mat4 VP) const {
//    b.draw(VP);
//    m.draw(VP, glm::vec2{0, 0});
//    im.draw(VP);
//    p.draw(VP);
}

void game::draw3d(glm::mat4 VP) const {
    b.draw(VP);
    m.draw(VP, -(glm::vec2{row * w, col * h} / 2.0f));
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
