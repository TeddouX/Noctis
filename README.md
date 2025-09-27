# Noctis: a simplistic game engine  
/!\ In developement  
Linux and MacOS support will be added in the late future.  
A public [Trello board](https://trello.com/b/By0OcR3N/noctis) is available for anyone to see. If you have an ideas for a feature, feel free to create a GitHub [issue](https://github.com/TeddouX/Noctis/issues/new) with the __enhancement__ label.

### Build locally

__[CMake](https://cmake.org/) is required.__  
Run:
```cmd
cmake -S . -B build
```
to build the CMake cache and install required libraries.  

And finally:
```cmd
mkdir build
cmake --build .\build\
```
to build the project.

### Credits
- [Glfw3](https://github.com/glfw/glfw) - A multi-platform library for OpenGL, OpenGL ES, Vulkan, window and input
- [GLM](https://github.com/g-truc/glm) - OpenGL Mathematics
- [Glad](https://github.com/Dav1dde/glad) - Multi-Language Vulkan/GL/GLES/EGL/GLX/WGL Loader-Generator based on the official specs. Use [this](https://gen.glad.sh/) to generate a loader.