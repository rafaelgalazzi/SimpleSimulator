#ifndef FPS_TIMER_H
#define FPS_TIMER_H
#include <stdbool.h>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <time.h>
#endif

void sleep_in_milliseconds(double time);
void fps_frame_control(double start_frame_time, double target_frame_time, bool is_enable);

#endif