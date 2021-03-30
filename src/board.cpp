//
// Created by captain on 3/30/21.
//
#include <algorithm>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>


#include <board.h>
#include <matrices.h>

board::board(glm::vec2 _pos, float _w, float _h) : position{_pos}, width{_w}, height{_h} {
    init();
}

void board::draw(glm::mat4 VP) const {
    auto translate = glm::translate(glm::vec3{this->position, 0});
    auto M = translate;
    auto MVP = VP * M;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    drawObject(this->object);
}

inline void board::init() {
    GLfloat vertex_buffer_data[] = {
            position.x + width, position.y + height,
            position.x + width, position.y - height,
            position.x - width, position.y - height,
            position.x - width, position.y + height,
    };
    GLfloat color_buffer_data[12];
    std::fill(color_buffer_data, color_buffer_data + 12, 0.2);
    this->object = create2DObject(GL_TRIANGLE_FAN, 4, vertex_buffer_data, color_buffer_data);
}

wall::wall(glm::vec3 _pos) : position{_pos} {
    init();
}

void wall::draw(glm::mat4 VP) {

}

inline void wall::init() {

}


