// Enable the Nuklear features required by the OpenGL backend.
#define NK_IMPLEMENTATION
#define NK_GLFW_GL3_IMPLEMENTATION
#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT

// Let GLAD provide OpenGL declarations on every supported platform.
#define GLFW_INCLUDE_NONE
#include <glad/gl.h>
#include <GLFW/glfw3.h>

// Include Nuklear after its configuration macros and graphics dependencies.
#include "nuklear.h"
#include "nuklear_glfw_gl3.h"

#include <stdlib.h>
#include "./simulation/physics.h"
#include "./simulation/drawn.h"
#include "./simulation/entity.h"
#include "./simulation/fps_timer.h"
#include "./simulation/config.h"

int main()
{
    // Initialize GLFW and request a context that supports legacy OpenGL calls.
    if (!glfwInit())
        return 1;

    // Fps limit control
    const double target_frame_time = 1.0 / TARGET_FPS;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
    GLFWwindow *window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Simulation Panel", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    if (!gladLoadGL(glfwGetProcAddress))
    {
        glfwDestroyWindow(window);
        glfwTerminate();
        return 1;
    }

    // Set up the Nuklear context.
    struct nk_glfw glfw = {0};
    struct nk_context *ctx = nk_glfw3_init(&glfw, window, NK_GLFW3_INSTALL_CALLBACKS);
    struct nk_font_atlas *atlas;
    nk_glfw3_font_stash_begin(&glfw, &atlas);
    nk_glfw3_font_stash_end(&glfw);

    // Simulation variables
    float sim_speed = 1.0f;
    int is_running = 0;

    // Setup particles
    float redColor[3] = {1.0f, 0, 0};
    Point simplePoint = create_point(0, 0, 1.0f, 1.0f, 2.0f, 10.0f, redColor);

    while (!glfwWindowShouldClose(window))
    {
        double frame_start = glfwGetTime();

        glfwPollEvents();
        nk_glfw3_new_frame(&glfw);

        /* --- 3. DESIGN THE SIMULATION GUI PANEL --- */
        if (nk_begin(ctx, "Simulation Controls", nk_rect(10, 10, 230, 250),
                     NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_SCALABLE | NK_WINDOW_TITLE))
        {

            // Text label
            nk_layout_row_dynamic(ctx, 20, 1);
            nk_label(ctx, "Control variables below:", NK_TEXT_LEFT);

            // Simulation toggle button
            nk_layout_row_dynamic(ctx, 30, 1);
            if (nk_button_label(ctx, is_running ? "Pause Sim" : "Start Sim"))
            {
                is_running = !is_running;
            }

            // Speed slider
            nk_layout_row_dynamic(ctx, 25, 1);
            nk_property_float(ctx, "Sim Speed:", 0.1f, &sim_speed, 10.0f, 0.1f, 0.05f);
        }
        nk_end(ctx);

        /* --- 4. RENDER PHYSICS & OPENGL SCENE --- */
        int framebuffer_width;
        int framebuffer_height;
        glfwGetFramebufferSize(window, &framebuffer_width, &framebuffer_height);

        setup2D(&framebuffer_width, &framebuffer_height);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (is_running)
        {
            // Apply all physics here
            applyPhysics(&simplePoint);
        }
        // Draw simulation geometry here (3D cubes, particle grids, fields, etc.).
        drawnFrame(&simplePoint);

        /* --- 5. RENDER THE GUI OVERLAY --- */
        glDisable(GL_DEPTH_TEST); // Keep the UI above the 3D scene.
        nk_glfw3_render(&glfw, NK_ANTI_ALIASING_ON, 512 * 1024, 128 * 1024);
        glEnable(GL_DEPTH_TEST);

        glfwSwapBuffers(window);

        fps_frame_control(frame_start, target_frame_time, true);
    }

    nk_glfw3_shutdown(&glfw);
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
