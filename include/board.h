//
// Created by captain on 3/30/21.
//

#ifndef CG_ASSIGNMENT_BOARD_H
#define CG_ASSIGNMENT_BOARD_H

#include <vector>

#include <glm/glm.hpp>
#include <nonedit.h>

struct board {
    glm::vec2 position{};
    float width{}, height{};

    board() = default;

    board(glm::vec2, float, float);

    void draw(glm::mat4) const;

    void init();

    VAO *object = nullptr;
};

struct wall {
    glm::vec2 start;
    glm::vec2 end;

    explicit wall(glm::vec2, glm::vec2);
};

struct maze {
    std::vector<wall> walls;
    float size{};

    maze() = default;

    explicit maze(float _size) : size{_size} {};

    void init();

    void draw(glm::mat4, glm::vec2) const;

    void add_wall(wall);

    VAO *object = nullptr;

};


#endif //CG_ASSIGNMENT_BOARD_H
