# Simple Simulator with OpenGL
This project uses CMake, GLFW, OpenGL, GLAD, and Nuklear. It currently requests
an OpenGL 3.3 Compatibility Profile so that legacy drawing functions such as
`glBegin` and `glVertex2f` can be used. CMake downloads GLFW 3.4 during the first
configuration, so an internet connection is required for the first build.

## Windows

Install CMake and Visual Studio with the **Desktop development with C++** workload,
then run:

```powershell
.\build.ps1
```

## Linux

Install a C compiler, CMake, Git, and the OpenGL and X11/Wayland development
packages supplied by your distribution. Then run:

```sh
sh ./build.sh
```

## macOS limitation

Apple does not provide a modern OpenGL Compatibility Profile. This legacy version
therefore targets Windows and Linux. Restoring the shader-based point renderer and
Core Profile context is required for current macOS support.

Each operating system produces its own native executable. A binary built on one
operating system cannot run natively on another operating system.

#

Run with "& .\build\Debug\simulator.exe"