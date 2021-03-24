//
// Created by captain on 3/24/21.
//

#ifndef CG_ASSIGNMENT_MATRICES_H
#define CG_ASSIGNMENT_MATRICES_H

struct GLMatrices {
    glm::mat4 projection;
    glm::mat4 model;
    glm::mat4 view;
    GLuint MatrixID;
};

extern GLMatrices Matrices;

#endif //CG_ASSIGNMENT_MATRICES_H
