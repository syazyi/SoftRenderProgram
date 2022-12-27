#ifndef KRENDER_TIMER_H
#define KRENDER_TIMER_H
#include <chrono>
namespace krender
{
    //caculate fps
    class Timer{
    public:
        Timer();

        float CaculateDeltaTime();

        ~Timer();
    private:
        std::chrono::steady_clock::time_point tp_start;
    };
} // namespace krender

#endif