//
// Created by captain on 3/24/21.
//

#ifndef CG_ASSIGNMENT_NONEDIT_H
#define CG_ASSIGNMENT_NONEDIT_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>

struct color_t {
    int r;
    int g;
    int b;
};

struct VAO {
    GLuint VertexArrayID;
    GLuint VertexBuffer;
    GLuint ColorBuffer;
    GLuint NormalBuffer;

    GLenum PrimitiveMode;
    GLenum FillMode;
    int NumVertices;
};

void setProgramFloat(GLuint& ID, const std::string &name, float value);

void setProgramVec3(GLuint& ID, const std::string &name, const glm::vec3 &value);

GLFWwindow *initGLFW(int width, int height);

GLuint LoadShaders(const char *vertex_file_path,
                   const char *fragment_file_path);

/* Generate VAO, VBOs and return VAO handle - Common Color for all vertices */
VAO *create3DObject(GLenum primitive_mode, int numVertices,
                    const GLfloat *vertex_buffer_data,
                    const GLfloat *color_buffer_data,
                    const GLfloat *normal_buffer_data,
                    GLenum fill_mode = GL_FILL);

VAO *create3DObject(GLenum primitive_mode,
                    int numVertices,
                    const GLfloat *vertex_buffer_data,
                    GLfloat red, GLfloat green, GLfloat blue,
                    const GLfloat *normal_buffer_data,
                    GLenum fill_mode = GL_FILL);

VAO *create3DObject(GLenum primitive_mode, int numVertices,
                    const GLfloat *vertex_buffer_data, color_t color,
                    const GLfloat *normal_buffer_data,
                    GLenum fill_mode = GL_FILL);

VAO *create2DObject(GLenum primitive_mode, int numVertices,
                    const GLfloat *vertex_buffer_data,
                    const GLfloat *color_buffer_data,
                    GLenum fill_mode = GL_FILL);

VAO *create2DObject(GLenum primitive_mode, int numVertices,
                    const GLfloat *vertex_buffer_data, GLfloat red,
                    GLfloat green, GLfloat blue, GLenum fill_mode);

VAO *create2DObject(GLenum primitive_mode, int numVertices,
                    const GLfloat *vertex_buffer_data, color_t color,
                    GLenum fill_mode);


void drawObject(struct VAO *vao);

void draw3DObject(struct VAO* vao);

#endif // CG_ASSIGNMENT_NONEDIT_H
