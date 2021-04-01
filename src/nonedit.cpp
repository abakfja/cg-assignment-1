//
// Created by captain on 3/24/21.
//

#include <fstream>
#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS

#include <input.h>
#include <nonedit.h>
#include <window.h>

/* Initialise glfw window, I/O callbacks and the renderer to use */
/* Nothing to Edit here */
GLFWwindow *initGLFW(int width, int height) {
    GLFWwindow *window; // window desciptor/handle

    glfwSetErrorCallback(error_callback);
    if (!glfwInit()) {
        // exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, "Among Us but worse", nullptr, nullptr);

    if (!window) {
        glfwTerminate();
        // exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);

    // Initialize GLEW, Needed in Core profile
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        std::cerr << "Error: Failed to initialise GLEW : "
                  << glewGetErrorString(err) << std::endl;
        exit(1);
    }

    glfwSwapInterval(1);

    /* --- register callbacks with GLFW --- */

    /* Register function to handle window resizes */
    /* With Retina display on Mac OS X GLFW's FramebufferSize
       is different from WindowSize */
    glfwSetFramebufferSizeCallback(window, reshapeWindow);
    glfwSetWindowSizeCallback(window, reshapeWindow);

    /* Register function to handle window close */
    glfwSetWindowCloseCallback(window, quit);

    /* Register function to handle keyboard input */
    glfwSetKeyCallback(window, keyboard);  // general keyboard input
    glfwSetCharCallback(window, keyboardChar); // simpler specific character handling

    /* Register function to handle mouse click */
    glfwSetMouseButtonCallback(window, mouseButton); // mouse button clicks
    glfwSetScrollCallback(window, scroll_callback);

    return window;
}

void setProgramFloat(GLuint& ID, const std::string &name, float value) {
//    std::cout << name << " " << glGetUniformLocation(ID, name.c_str()) << std::endl;
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void setProgramVec3(GLuint& ID, const std::string &name, const glm::vec3 &value) {
//    std::cout << name << " " << glGetUniformLocation(ID, name.c_str()) << std::endl;
    glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

/* Function to load Shaders - Use it as it is */
GLuint LoadShaders(const char *vertex_file_path, const char *fragment_file_path) {

    // Create the shaders
    GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    // Read the Vertex Shader code from the file
    std::string VertexShaderCode;
    std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
    if (VertexShaderStream.is_open()) {
        std::string Line;
        while (std::getline(VertexShaderStream, Line)) {
            VertexShaderCode += "\n" + Line;
        }
        VertexShaderStream.close();
    }

    // Read the Fragment Shader code from the file
    std::string FragmentShaderCode;
    std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
    if (FragmentShaderStream.is_open()) {
        std::string Line;
        while (std::getline(FragmentShaderStream, Line))
            FragmentShaderCode += "\n" + Line;
        FragmentShaderStream.close();
    }

    GLint Result = GL_FALSE;
    int InfoLogLength;

    // Compile Vertex Shader
    printf("Compiling shader : %s\n", vertex_file_path);
    char const *VertexSourcePointer = VertexShaderCode.c_str();

    glShaderSource(VertexShaderID, 1, &VertexSourcePointer, nullptr);
    glCompileShader(VertexShaderID);

    // Check Vertex Shader
    glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    std::vector<char> VertexShaderErrorMessage(InfoLogLength);
    glGetShaderInfoLog(VertexShaderID, InfoLogLength, nullptr, &VertexShaderErrorMessage[0]);
    fprintf(stdout, "%s\n", &VertexShaderErrorMessage[0]);

    // Compile Fragment Shader
    printf("Compiling shader : %s\n", fragment_file_path);
    char const *FragmentSourcePointer = FragmentShaderCode.c_str();
    glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, nullptr);
    glCompileShader(FragmentShaderID);

    // Check Fragment Shader
    glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    std::vector<char> FragmentShaderErrorMessage(InfoLogLength);
    glGetShaderInfoLog(FragmentShaderID, InfoLogLength, nullptr, &FragmentShaderErrorMessage[0]);
    fprintf(stdout, "%s\n", &FragmentShaderErrorMessage[0]);

    // Link the program
    fprintf(stdout, "Linking program\n");
    GLuint ProgramID = glCreateProgram();
    glAttachShader(ProgramID, VertexShaderID);
    glAttachShader(ProgramID, FragmentShaderID);
    glLinkProgram(ProgramID);

    // Check the program
    glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
    glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    std::vector<char> ProgramErrorMessage(std::max(InfoLogLength, int(1)));
    glGetProgramInfoLog(ProgramID, InfoLogLength, nullptr, &ProgramErrorMessage[0]);
    fprintf(stdout, "%s\n", &ProgramErrorMessage[0]);

    glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);

    return ProgramID;
}


/**
 *
 * 3d Object Vertex attribute declaration
 *
 */
/* Generate VAO, VBOs and return VAO handle */
VAO *create3DObject(GLenum primitive_mode, int numVertices, const GLfloat *vertex_buffer_data,
                    const GLfloat *color_buffer_data, const GLfloat *normal_buffer_data, GLenum fill_mode) {
    auto *vao = new VAO;
    vao->PrimitiveMode = primitive_mode;
    vao->NumVertices = numVertices;
    vao->FillMode = fill_mode;

    // Create Vertex Array Object
    // Should be done after CreateWindow and before any other GL calls
    glGenVertexArrays(1, &(vao->VertexArrayID)); // VAO
    glGenBuffers(1, &(vao->VertexBuffer));       // VBO - vertices
    glGenBuffers(1, &(vao->ColorBuffer));        // VBO - colors
    glGenBuffers(1, &(vao->NormalBuffer));        // VBO - colors


    glBindVertexArray(vao->VertexArrayID);            // Bind the VAO
    glBindBuffer(GL_ARRAY_BUFFER, vao->VertexBuffer); // Bind the VBO vertices
    glBufferData(GL_ARRAY_BUFFER, 3 * numVertices * sizeof(GLfloat), vertex_buffer_data,
                 GL_STATIC_DRAW); // Copy the vertices into VBO
    glVertexAttribPointer(
            0,                            // attribute 0. Vertices
            3,                            // size (x,y,z)
            GL_FLOAT,                     // type
            GL_FALSE,                     // normalized?
            0,                            // stride
            (void *) nullptr                      // array buffer offset
    );

    glBindBuffer(GL_ARRAY_BUFFER, vao->ColorBuffer); // Bind the VBO colors
    glBufferData(GL_ARRAY_BUFFER, 3 * numVertices * sizeof(GLfloat), color_buffer_data,
                 GL_STATIC_DRAW); // Copy the vertex colors
    glVertexAttribPointer(
            1,                            // attribute 1. Color
            3,                            // size (r,g,b)
            GL_FLOAT,                     // type
            GL_FALSE,                     // normalized?
            0,                            // stride
            (void *) nullptr                    // array buffer offset
    );

    glBindBuffer(GL_ARRAY_BUFFER, vao->NormalBuffer); // Bind the VBO vertices
    glBufferData(GL_ARRAY_BUFFER, 3 * numVertices * sizeof(GLfloat), normal_buffer_data,
                 GL_STATIC_DRAW); // Copy the vertices into VBO
    glVertexAttribPointer(
            2,                            // attribute 2. normals
            3,                            // size (x,y,z)
            GL_FLOAT,                     // type
            GL_FALSE,                     // normalized?
            0,                            // stride
            (void *) nullptr                      // array buffer offset
    );

    return vao;
}

/* Generate VAO, VBOs and return VAO handle - Common Color for all vertices */
VAO *create3DObject(GLenum primitive_mode, int numVertices,
                    const GLfloat *vertex_buffer_data, const GLfloat red,
                    const GLfloat green, const GLfloat blue, const GLfloat *normal_buffer_data, GLenum fill_mode) {
    auto *color_buffer_data = new GLfloat[3 * numVertices];
    for (int i = 0; i < numVertices; i++) {
        color_buffer_data[3 * i] = red;
        color_buffer_data[3 * i + 1] = green;
        color_buffer_data[3 * i + 2] = blue;
    }

    return create3DObject(primitive_mode, numVertices, vertex_buffer_data,
                          color_buffer_data, normal_buffer_data, fill_mode);
}

VAO *create3DObject(GLenum primitive_mode, int numVertices,
                    const GLfloat *vertex_buffer_data, const color_t color, const GLfloat *normal_buffer_data,
                    GLenum fill_mode) {
    return create3DObject(primitive_mode, numVertices, vertex_buffer_data,
                          color.r / 256.0, color.g / 256.0, color.b / 256.0, normal_buffer_data,
    fill_mode);
}



/**
 *
 * 2d Object Vertex attribute declaration
 *
 */
/* Generate VAO, VBOs and return VAO handle */
VAO *create2DObject(GLenum primitive_mode, int numVertices,
                    const GLfloat *vertex_buffer_data,
                    const GLfloat *color_buffer_data, GLenum fill_mode) {
    auto *vao = new struct VAO;
    vao->PrimitiveMode = primitive_mode;
    vao->NumVertices = numVertices;
    vao->FillMode = fill_mode;
    // Create Vertex Array Object
    // Should be done after CreateWindow and before any other GL calls
    glGenVertexArrays(1, &(vao->VertexArrayID)); // VAO
    glGenBuffers(1, &(vao->VertexBuffer));       // VBO - vertices
    glGenBuffers(1, &(vao->ColorBuffer));        // VBO - colors

    glBindVertexArray(vao->VertexArrayID);            // Bind the VAO
    glBindBuffer(GL_ARRAY_BUFFER, vao->VertexBuffer); // Bind the VBO vertices
    // Copy the vertices into VBO
    glBufferData(GL_ARRAY_BUFFER, 2 * numVertices * sizeof(GLfloat), vertex_buffer_data, GL_STATIC_DRAW);
    glVertexAttribPointer(
            0,                  // attribute 0. Vertices
            2,                  // size (x,y)
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void *) nullptr    // array buffer offset
    );

    glBindBuffer(GL_ARRAY_BUFFER, vao->ColorBuffer); // Bind the VBO colors
    glBufferData(GL_ARRAY_BUFFER, 3 * numVertices * sizeof(GLfloat), color_buffer_data,
                 GL_STATIC_DRAW); // Copy the vertex colors
    glVertexAttribPointer(
            1,   // attribute 1. Color
            3,       // size (r,g,b)
            GL_FLOAT,                     // type
            GL_FALSE,                     // normalized?
            0,                            // stride
            (void *) nullptr                    // array buffer offset
    );

    return vao;
}

/* Generate VAO, VBOs and return VAO handle - Common Color for all vertices */
VAO *create2DObject(GLenum primitive_mode, int numVertices,
                    const GLfloat *vertex_buffer_data, const GLfloat red,
                    const GLfloat green, const GLfloat blue, GLenum fill_mode) {
    auto *color_buffer_data = new GLfloat[3 * numVertices];
    for (int i = 0; i < numVertices; i++) {
        color_buffer_data[3 * i] = red;
        color_buffer_data[3 * i + 1] = green;
        color_buffer_data[3 * i + 2] = blue;
    }
    return create2DObject(primitive_mode, numVertices, vertex_buffer_data, color_buffer_data, fill_mode);
}

VAO *create2DObject(GLenum primitive_mode, int numVertices,
                    const GLfloat *vertex_buffer_data, const color_t color,
                    GLenum fill_mode) {
    return create2DObject(primitive_mode, numVertices, vertex_buffer_data,
                          color.r / 256.0, color.g / 256.0, color.b / 256.0,
                          fill_mode);
}


/* Render the VBOs handled by VAO */
void drawObject(struct VAO *vao) {
    // Change the Fill Mode for this object
    glPolygonMode(GL_FRONT_AND_BACK, vao->FillMode);

    // Bind the VAO to use
    glBindVertexArray(vao->VertexArrayID);

    // Enable Vertex Attribute 0 - 3d Vertices
    glEnableVertexAttribArray(0);
    // Bind the VBO to use
    glBindBuffer(GL_ARRAY_BUFFER, vao->VertexBuffer);

    // Enable Vertex Attribute 1 - Color
    glEnableVertexAttribArray(1);
    // Bind the VBO to use
    glBindBuffer(GL_ARRAY_BUFFER, vao->ColorBuffer);

    // Draw the geometry !
    glDrawArrays(vao->PrimitiveMode, 0, vao->NumVertices); // Starting from vertex 0; 3 vertices total -> 1 triangle
}

/* Render the VBOs handled by VAO */
void draw3DObject(struct VAO *vao) {

    // Change the Fill Mode for this object
    glPolygonMode(GL_FRONT_AND_BACK, vao->FillMode);

    // Bind the VAO to use
    glBindVertexArray(vao->VertexArrayID);

    // Enable Vertex Attribute 0 - 3d Vertices
    glEnableVertexAttribArray(0);
    // Bind the VBO to use
    glBindBuffer(GL_ARRAY_BUFFER, vao->VertexBuffer);

    // Enable Vertex Attribute 1 - Color
    glEnableVertexAttribArray(1);
    // Bind the VBO to use
    glBindBuffer(GL_ARRAY_BUFFER, vao->ColorBuffer);

    // Enable Vertex Attribute 2 - Normals
    glEnableVertexAttribArray(2);
    // Bind the VBO to use
    glBindBuffer(GL_ARRAY_BUFFER, vao->NormalBuffer);

    // Draw the geometry !
    glDrawArrays(vao->PrimitiveMode, 0, vao->NumVertices); // Starting from vertex 0; 3 vertices total -> 1 triangle
}
