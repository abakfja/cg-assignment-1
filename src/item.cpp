//
// Created by captain on 3/30/21.
//

#include <tuple>
#include <item.h>
#include <matrices.h>
#include <iostream>

item::item(glm::vec2 vec) : position(vec) {
}

glm::vec2 item::set_position(glm::vec2 vec) {
    return position = vec;
}

void item::init() {
    auto *vertex_buffer_data = new GLfloat[300];
    auto *normal_buffer_data = new GLfloat[300];
    auto alpha = 2 * glm::pi<GLfloat>() / 100;
    for (int i = 0; i < 100; i++) {
        std::tie(vertex_buffer_data[3 * i], vertex_buffer_data[3 * i + 1],
                 vertex_buffer_data[3 * i + 2]) = std::make_tuple(
                size * std::cos(i * alpha), size * std::sin(i * alpha), 0.0f);
    }
    std::fill(normal_buffer_data, normal_buffer_data + 300, 0.0f);
    for (int i = 0; i < 100; i++) normal_buffer_data[3 * i + 2] = 1.0f;
    this->object = create3DObject(GL_TRIANGLE_FAN, 100, vertex_buffer_data, color, normal_buffer_data,
                                  GL_FILL);
}

void item::draw(glm::mat4 VP) const {
    auto M = glm::translate(glm::vec3{position, 0});
    auto MVP = VP * M;
    glUniformMatrix4fv(Matrices.mvpId, 1, GL_FALSE, &MVP[0][0]);
    glUniformMatrix4fv(Matrices.modelId, 1, GL_FALSE, &M[0][0]);
    draw3DObject(this->object);
}
