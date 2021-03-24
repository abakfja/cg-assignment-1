//
// Created by captain on 3/24/21.
//

#ifndef CG_ASSIGNMENT_WINDOW_H
#define CG_ASSIGNMENT_WINDOW_H

extern void reset_screen();

void error_callback(int error, const char *description);

void quit(GLFWwindow *window);

void reshapeWindow(GLFWwindow *window, int width, int height);

#endif //CG_ASSIGNMENT_WINDOW_H
