//
// Created by captain on 3/29/21.
//

#ifndef CG_ASSIGNMENT_BEAN_H
#define CG_ASSIGNMENT_BEAN_H

#include <nonedit.h>
#include <glm/glm.hpp>
#include <string>

struct bean {

    VAO *object = nullptr;
    glm::vec2 position{};
    float speed{};
    std::string resource;
    bool orientation = true;

    bean() = default;

    bean(glm::vec2 vec, float d, std::string string);

    glm::vec2 set_position(glm::vec2);

    void tick();

    void init();

    GLfloat top() const {
        return position.y + 1.0;
    }

    GLfloat bottom() const {
        return position.y - 0.5;
    }

    GLfloat left() const {
        return position.x - 0.65;
    }

    GLfloat right() const {
        return position.x + 0.65;
    }

    GLfloat get_orientation() const {
        return orientation ? -1.0f : 1.0f;
    };

    void draw(glm::mat4 VP) const;
};


#endif //CG_ASSIGNMENT_BEAN_H
