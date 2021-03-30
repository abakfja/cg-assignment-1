//
// Created by captain on 3/29/21.
//
#include <vector>
#include <iostream>
#include <fstream>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include <bean.h>
#include <matrices.h>


glm::vec2 bean::set_position(glm::vec2 _pos) {
    this->position = _pos;
    return this->position;
}

void bean::tick() {
}

void bean::draw(glm::mat4 VP) const {
    auto orientation = glm::scale(glm::vec3{1.0f, 1.0f, 1.0f});
    auto translate = glm::translate(glm::vec3{this->position, 0});
    auto M = translate * orientation;
    auto MVP = VP * M;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    drawObject(this->object);
}

void bean::init() {
    std::vector<GLfloat> vertices;
    std::vector<GLfloat> colours;
    std::ifstream vert_stream(this->resource, std::ios::in);
    while (vert_stream.is_open()) {
        double x, y;
        double r, g, b;
        vert_stream >> x >> y;
        vert_stream >> r >> g >> b;
        if (vert_stream.eof()) {
            break;
        }
        vertices.push_back(x);
        vertices.push_back(y);
        colours.push_back(r / 255);
        colours.push_back(g / 255);
        colours.push_back(b / 255);
    }
    auto *vertex_buffer_data = new GLfloat[vertices.size()];
    auto *color_buffer_data = new GLfloat[colours.size()];
    std::copy(vertices.begin(), vertices.end(), vertex_buffer_data);
    std::copy(colours.begin(), colours.end(), color_buffer_data);
    this->object = create2DObject(GL_TRIANGLES, vertices.size() >> 1, vertex_buffer_data, color_buffer_data, GL_FILL);
}

bean::bean(glm::vec2 vec, float d, std::string str) : position{vec}, speed{d}, resource{std::move(str)} {
}


