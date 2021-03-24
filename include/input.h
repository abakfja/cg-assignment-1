//
// Created by captain on 3/24/21.
//

#ifndef CG_ASSIGNMENT_INPUT_H
#define CG_ASSIGNMENT_INPUT_H

extern void keyboard(GLFWwindow *window, int key, int scancode, int action, int mods);

extern void keyboardChar(GLFWwindow *window, unsigned int key);

extern void mouseButton(GLFWwindow *window, int button, int action, int mods);

extern void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

#endif //CG_ASSIGNMENT_INPUT_H
