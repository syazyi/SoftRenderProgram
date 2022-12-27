#include <iostream>
#include "timer.h"

namespace krender
{
    Timer::Timer() : tp_start(std::chrono::high_resolution_clock::now()){}

    float Timer::CaculateDeltaTime()
    {
        float delta;
        auto tp_current = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::duration<float>>(tp_current - tp_start).count();
        tp_start = tp_current;
        delta = duration;
        std::cout << "\r" << 1.f / duration << " FPS"; 
        return delta;
    }

    Timer::~Timer(){
        /*auto tp_end = std::chrono::high_resolution_clock::now();
        auto durationTimes = std::chrono::duration_cast<std::chrono::duration<float>>(tp_end - tp_start).count();
        std::cout << "\r" << 1.f / durationTimes << " FPS";*/
    }
} // namespace krender
