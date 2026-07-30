cmake_minimum_required(VERSION 3.10)
project(SimpleSimulator C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

include(FetchContent)

# Keep third-party binaries out of the repository and make setup reproducible.
FetchContent_Declare(glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.4
    GIT_SHALLOW TRUE
)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(glfw)

# Use the native OpenGL implementation on Windows, Linux, and macOS.
find_package(OpenGL REQUIRED)

# Build the application with the local Nuklear headers and GLFW's GLAD loader.
add_executable(SimulationApp src/main.c)
target_include_directories(SimulationApp PRIVATE include)
target_include_directories(SimulationApp PRIVATE "${glfw_SOURCE_DIR}/deps")

# GLFW selects its native platform backend during configuration.
target_link_libraries(SimulationApp PRIVATE glfw OpenGL::GL)
