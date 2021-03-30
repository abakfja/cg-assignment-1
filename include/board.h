//
// Created by captain on 3/30/21.
//

#ifndef CG_ASSIGNMENT_BOARD_H
#define CG_ASSIGNMENT_BOARD_H

#include <glm/glm.hpp>
#include <nonedit.h>

struct board {
    glm::vec2 position;
    float width, height;

    explicit board(glm::vec2, float, float);

    void draw(glm::mat4) const;

    void init();

    VAO *object = nullptr;
};

struct wall {
    glm::vec3 position;


    explicit wall(glm::vec3);

    void draw(glm::mat4);

    void init();

    VAO *object = nullptr;
};


#endif //CG_ASSIGNMENT_BOARD_H
