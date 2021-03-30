//
// Created by captain on 3/24/21.
//
#include <iostream>

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <ft2build.h>
#include <window.h>
#include <matrices.h>
#include <nonedit.h>
#include <timer.h>
#include <player.h>
#include <game.h>

GLMatrices Matrices;
GLuint programID;
GLFWwindow *window;
game amongus;

const color_t COLOR_BACKGROUND = {123, 34, 0};

Timer t60(1.0 / 60);

float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;

void reset_screen() {
    float top = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left = screen_center_x - 4 / screen_zoom;
    float right = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}


/* Add all the models to be created here */
void initGL(GLFWwindow *glfwWindow, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models
    amongus.init();

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("../src/shaders/shader.vert", "../src/shaders/shader.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");

    reshapeWindow(glfwWindow, width, height);

    // Background color of the scene
    glClearColor(COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0,
                 0.0f); // R, G, B, A
    glClearDepth(1.0f);

    // Enable Depth Test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LEQUAL);

    std::cout << "VENDOR: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "RENDERER: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "VERSION: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
}

void draw() {
    // clear the color and depth in the frame buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    glUseProgram(programID);

    // Target - Where is the camera looking at.
    Matrices.view = glm::lookAt(glm::vec3{amongus.p.position, 10},
                                glm::vec3{amongus.p.position, 0},
                                glm::vec3{0, 1, 0});

    // Compute Camera matrix (view)
    //Matrices.projection = glm::ortho(-3.0f, 3.0f, -3.0f, 3.0f, 1.0f, 0.1f);
    Matrices.projection = glm::perspective((float) glm::radians(45.0), 1.0f, 1.0f, -1.0f);

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!

    // Scene render
    amongus.draw(VP);
}

void tick_elements() {

}

void tick_input(GLFWwindow *glfwWindow) {
    int keys[4];
    keys[0] = glfwGetKey(glfwWindow, GLFW_KEY_A);
    keys[1] = glfwGetKey(glfwWindow, GLFW_KEY_D);
    keys[2] = glfwGetKey(glfwWindow, GLFW_KEY_W);
    keys[3] = glfwGetKey(glfwWindow, GLFW_KEY_S);
    amongus.get_input(keys);
}

int main(int argc, char **argv) {
    int width = 600;
    int height = 600;

    window = initGLFW(width, height);

    initGL(window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.process_tick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}