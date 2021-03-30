//
// Created by captain on 3/29/21.
//

#ifndef CG_ASSIGNMENT_BEAN_H
#define CG_ASSIGNMENT_BEAN_H

#include <nonedit.h>
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <string>

struct bean {

    VAO *object = nullptr;
    glm::vec2 position{};
    float speed{};
    std::string resource;

    bean() = default;

    bean(glm::vec2 vec, float d, std::string string);

    glm::vec2 set_position(glm::vec2);

    void tick();

    void init();

    void draw(glm::mat4 VP) const;
};


#endif //CG_ASSIGNMENT_BEAN_H
