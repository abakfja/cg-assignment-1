//
// Created by captain on 3/24/21.
//

#include <GLFW/glfw3.h>
#include <timer.h>

Timer::Timer(double interval) noexcept {
    prev = 0;
    this->interval = interval;
}

bool Timer::process_tick() {
    double cur = glfwGetTime();
    if (cur - prev >= interval) {
        prev = cur;
        return true;
    } else {
        return false;
    }
}
