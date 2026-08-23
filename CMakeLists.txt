cmake_minimum_required(VERSION 3.10)

project(SimpleSimulator C)

# Use the native OpenGL implementation on Windows, Linux, and macOS.
find_package(OpenGL REQUIRED)
find_package(OpenMP REQUIRED)
# Build the application with the local Nuklear headers and GLFW's GLAD loader.

add_executable(simulator 
    src/main.c 
    src/simulation/drawn/drawn.c
    src/simulation/physics/physics.c
    src/simulation/fps_timer/fps_timer.c
    src/simulation/entity/entity.c
)

target_include_directories(simulator PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include/GLFW
    ${CMAKE_CURRENT_SOURCE_DIR}/include/glad
    ${CMAKE_CURRENT_SOURCE_DIR}/include/KHR
)

add_library(glad STATIC include/glad/src/gl.c)

target_include_directories(glad PUBLIC include)

# GLFW selects its native platform backend during configuration.
target_link_libraries(simulator PRIVATE 
    OpenGL::GL
    glad
    OpenMP::OpenMP_C
    ${CMAKE_CURRENT_SOURCE_DIR}/include/lib-vc2026/glfw3.lib
)
