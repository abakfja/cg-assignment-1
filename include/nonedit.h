//
// Created by captain on 3/24/21.
//

#ifndef CG_ASSIGNMENT_NONEDIT_H
#define CG_ASSIGNMENT_NONEDIT_H

#include <GLFW/glfw3.h>
#include <glad/glad.h>

struct color_t {
    int r;
    int g;
    int b;
};

struct VAO {
    GLuint VertexArrayID;
    GLuint VertexBuffer;
    GLuint ColorBuffer;

    GLenum PrimitiveMode;
    GLenum FillMode;
    int NumVertices;
};
typedef struct VAO VAO;

GLFWwindow *initGLFW(int width, int height);

GLuint LoadShaders(const char *vertex_file_path, const char *fragment_file_path);

struct VAO *create3DObject(GLenum primitive_mode, int numVertices, const GLfloat *vertex_buffer_data,
                           const GLfloat *color_buffer_data, GLenum fill_mode = GL_FILL);

struct VAO *create3DObject(GLenum primitive_mode, int numVertices, const GLfloat *vertex_buffer_data, GLfloat red,
                           GLfloat green, GLfloat blue, GLenum fill_mode = GL_FILL);

struct VAO *
create3DObject(GLenum primitive_mode, int numVertices, const GLfloat *vertex_buffer_data, color_t color,
               GLenum fill_mode = GL_FILL);

void draw3DObject(struct VAO *vao);

#endif //CG_ASSIGNMENT_NONEDIT_H
