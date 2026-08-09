#include "fps_timer.h"
#include <GLFW/glfw3.h>

// Sleep function
void sleep_in_milliseconds(double time_in_milliseconds)
{
#ifdef _WIN32
    Sleep((DWORD)time_in_milliseconds);

#else
    struct timespec ts;
    ts.tv_sec = ms / 1000;
    ts.tv_nsec = (long)(ms % 1000) * 1000000L;

    nanosleep(&ts, null)

#endif
}

// FPS limiter function
void fps_frame_control(double start_frame_time, double target_frame_time, bool is_enable)
{
    if (!is_enable)
        return;

    double elapsed_time = glfwGetTime() - start_frame_time;

    if (elapsed_time < target_frame_time)
    {
        double remaining_time = (target_frame_time - elapsed_time) * 1000;
        sleep_in_milliseconds(remaining_time);
    }
}