//
// Created by captain on 3/30/21.
//

#ifndef CG_ASSIGNMENT_ITEM_H
#define CG_ASSIGNMENT_ITEM_H


#include <nonedit.h>

struct item {
    VAO *object = nullptr;
    glm::vec2 position{};

    item() = default;
    int score = 0;
    color_t color{};
    GLfloat size = 0.5;

    GLfloat top() const {
        return position.y + size;
    }

    GLfloat bottom() const {
        return position.y - size;
    }

    GLfloat left() const {
        return position.x - size;
    }

    GLfloat right() const {
        return position.x + size;
    }

    glm::vec2 set_position(glm::vec2);

    void init();

    void draw(glm::mat4 VP) const;

    explicit item(glm::vec2 vec);
};


struct obstacle : item {
    explicit obstacle(glm::vec2 pos): item(pos) {
        color = color_t{10,10,10};
        score = -100;
        init();
    }
};


struct powerup : item {
    explicit powerup(glm::vec2 pos): item(pos) {
        color = color_t{222, 203, 0};
        score = 100;
        init();
    }
};


struct task : item {
    explicit task(glm::vec2 pos): item(pos) {
        color = color_t{222, 0, 222};
        score = 0;
        size = 1.0f;
        init();
    }
};

#endif //CG_ASSIGNMENT_ITEM_H
