//
// Created by captain on 3/24/21.
//

#ifndef CG_TIMER_H
#define CG_TIMER_H

class Timer {
public:
    Timer() = default;

    constexpr explicit Timer(double interval) noexcept;

    double interval{};

    bool process_tick();

private:
    double prev{};
};

#endif //CG_TIMER_H
