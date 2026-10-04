#include "fps_timer.h"
#include <GLFW/glfw3.h>
#ifndef _WIN32
#include <errno.h>
#endif

// Sleep function
void sleep_in_milliseconds(double time_in_milliseconds)
{
    if (time_in_milliseconds <= 0.0)
        return;

#ifdef _WIN32
    // High-resolution timers preserve fractional milliseconds on Windows.
    HANDLE timer = CreateWaitableTimerExW(NULL, NULL, 0x00000002,
                                          TIMER_MODIFY_STATE | SYNCHRONIZE);
    if (timer)
    {
        LARGE_INTEGER due_time;
        due_time.QuadPart = -(LONGLONG)(time_in_milliseconds * 10000.0);
        if (due_time.QuadPart == 0)
            due_time.QuadPart = -1;
        if (SetWaitableTimer(timer, &due_time, 0, NULL, NULL, FALSE))
            WaitForSingleObject(timer, INFINITE);
        CloseHandle(timer);
    }
    // If high-resolution timers are unavailable, the limiter's deadline
    // loop below still enforces the target without a coarse Sleep overshoot.

#else
    struct timespec ts;
    ts.tv_sec = (time_t)(time_in_milliseconds / 1000.0);
    ts.tv_nsec = (long)((time_in_milliseconds / 1000.0 - ts.tv_sec) * 1000000000.0);

    while (nanosleep(&ts, &ts) == -1 && errno == EINTR)
    {
    }

#endif
}

// FPS limiter function
void fps_frame_control(double start_frame_time, double target_frame_time, double *lastFrameTime, bool is_enable)
{
    double now = glfwGetTime();
    if (is_enable && target_frame_time > 0.0)
    {
        const double deadline = start_frame_time + target_frame_time;
        // Sleep for most of the remaining interval, then wait precisely for
        // the deadline. The short final spin avoids millisecond rounding.
        const double spin_margin = 0.001;
        if (deadline - now > spin_margin)
        {
            sleep_in_milliseconds((deadline - now - spin_margin) * 1000.0);
        }

        while (now < deadline)
        {
            now = glfwGetTime();
        }
    }
    if (lastFrameTime)
        *lastFrameTime = now;
}
