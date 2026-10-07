#include "timer.h"
#include <stdbool.h>
#include <GLFW/glfw3.h>

bool is_paused = true;
double last_paused_at = 0;
double time_paused = 0;

double get_physics_application_time()
{
    if (is_paused)
    {
        return last_paused_at - time_paused;
    }

    return get_real_application_time() - time_paused;
}

double get_real_application_time()
{
    return glfwGetTime();
}

void pause_application_time()
{
    if (is_paused)
    {
        time_paused += (get_real_application_time() - last_paused_at);
        is_paused = false;
        return;
    }
    last_paused_at = get_real_application_time();
    is_paused = true;
}