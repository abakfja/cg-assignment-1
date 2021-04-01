//
// Created by captain on 3/30/21.
//
#include <algorithm>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>


#include <board.h>
#include <matrices.h>
#include <iostream>

board::board(glm::vec2 _pos, GLfloat _w, GLfloat _h) : position{_pos}, width{_w}, height{_h} {
    init();
}

void board::draw(glm::mat4 VP) const {
    auto translate = glm::translate(glm::vec3{-width / 2, -height / 2, 0});
    auto M = translate;
    auto MVP = VP * M;
    glUniformMatrix4fv(Matrices.mvpId, 1, GL_FALSE, &MVP[0][0]);
    glUniformMatrix4fv(Matrices.modelId, 1, GL_FALSE, &M[0][0]);
    draw3DObject(this->object);
}

inline void board::init() {
    GLfloat vertex_buffer_data[18] = {
            position.x, position.y, 0,
            position.x + width, position.y, 0,
            position.x + width, position.y + height, 0,
            position.x + width, position.y + height, 0,
            position.x, position.y + height, 0,
            position.x, position.y, 0
    };
    GLfloat normal_buffer_data[18] = {
            0, 0, 1,
            0, 0, 1,
            0, 0, 1,
            0, 0, 1,
            0, 0, 1,
            0, 0, 1
    };
    GLfloat color_buffer_data[18];
    std::fill(color_buffer_data, color_buffer_data + 18, 0.3);
    this->object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, color_buffer_data, normal_buffer_data,
                                  GL_FILL);
}

wall::wall(glm::vec2 _st, glm::vec2 _nd) : start{_st}, end{_nd} {
}

void maze::init() {
    std::vector<GLfloat> vertices;
    std::vector<GLfloat> normals;
    std::vector<GLfloat> colours;
    auto add_pt = [&vertices](glm::vec3 pos) {
        vertices.push_back(pos.x);
        vertices.push_back(pos.y);
        vertices.push_back(pos.z);
    };
    auto add_normal = [&normals](GLfloat x, GLfloat y, GLfloat z) {
        normals.push_back(x);
        normals.push_back(y);
        normals.push_back(z);
    };
    for (const auto &x: walls) {
        for (int i = 0; i < 2; i++) {
            add_pt(glm::vec3{x.start, 0});
            add_pt(glm::vec3{x.end, 0});
            add_pt(glm::vec3{x.end, size});
            add_pt(glm::vec3{x.start, 0});
            add_pt(glm::vec3{x.start, size});
            add_pt(glm::vec3{x.end, size});
        }
        if (std::abs(x.start.x - x.end.x) < glm::epsilon<float>()) {
            for (int i = 0; i < 6; i++) add_normal(-1, 0, 0);
            for (int i = 0; i < 6; i++) add_normal(1, 0, 0);
        } else {
            for (int i = 0; i < 6; i++) add_normal(0, -1, 0);
            for (int i = 0; i < 6; i++) add_normal(0, 1, 0);
        }
    }
    std::cout << vertices.size() << std::endl;
    auto *vertex_buffer_data = new GLfloat[vertices.size()];
    std::copy(vertices.begin(), vertices.end(), vertex_buffer_data);
    auto *normal_buffer_data = new GLfloat[vertices.size()];
    std::copy(normals.begin(), normals.end(), normal_buffer_data);
    color_t color{0, 255, 0};
    this->object = create3DObject(GL_TRIANGLES,
                                  (int) vertices.size() / 3,
                                  vertex_buffer_data, color, normal_buffer_data, GL_FILL);
}

void maze::draw(glm::mat4 VP, glm::vec2 pos) const {
    auto translate = glm::translate(glm::vec3{pos, 0});
    auto M = translate;
    auto MVP = VP * M;
    glUniformMatrix4fv(Matrices.mvpId, 1, GL_FALSE, &MVP[0][0]);
    glUniformMatrix4fv(Matrices.modelId, 1, GL_FALSE, &M[0][0]);
    draw3DObject(this->object);
}

void maze::add_wall(wall w) {
    walls.push_back(w);
}
