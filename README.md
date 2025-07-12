# Unknown Engine: a simplistic game engine  
/!\ In developement  
Trying to reach a ratio of at least 1 comment for 10 lines of code (currently 1/17.3).

### Credits
- [Assimp](https://github.com/assimp/assimp) - The official Open-Asset-Importer-Library
- [Glfw3](https://github.com/glfw/glfw) - A multi-platform library for OpenGL, OpenGL ES, Vulkan, window and input
- [GLM](https://github.com/g-truc/glm) - OpenGL Mathematics
- [Dear ImGui](https://github.com/ocornut/imgui) - Bloat-free Graphical User interface for C++ with minimal dependencies
- [STB](https://github.com/nothings/stb) - Single-file public domain libraries for C/C++ (*Unknown Engine uses [stb_image.h](https://github.com/nothings/stb/blob/master/stb_image.h) for image loading*).
- [Glad](https://github.com/Dav1dde/glad) - Multi-Language Vulkan/GL/GLES/EGL/GLX/WGL Loader-Generator based on the official specs. Use [this](https://gen.glad.sh/) to generate a loader.
- [Nlohmann-json](https://github.com/nlohmann/json) - JSON for Modern C++
- [Fmt](https://github.com/fmtlib/fmt) - A modern formatting library
- [Boost-UUID](https://github.com/boostorg/uuid) - Boost.org uuid module

### Editor
The editor's UI is made using [Dear ImGui](https://github.com/ocornut/imgui).  
  
<img width="1920" height="1080" alt="Screenshot of Uknown Engine's editor's UI" src="https://github.com/user-attachments/assets/0673b0fa-722e-4579-9e54-8539cd8fa626" />

### Build locally

__[vcpkg](https://vcpkg.io/en/) and [Cmake](https://cmake.org/) are required.__  
For __vcpkg__, follow the installation guide on: [Microsoft Learn](https://learn.microsoft.com/en-us/vcpkg/get_started/get-started?pivots=shell-powershell#1---set-up-vcpkg).  
After installation, add the `vcpkg/bin` folder to __PATH__.   

After building the project, you will need to create a __`CMakeUserPresets.json`__ in the root, containing this (*replace `"PATH/TO/VCPKG"` with the actual path*): 
```json
{
  "version": 2,
  "configurePresets": [
    {
      "name": "default",
      "inherits": "vcpkg",
      "environment": {
        "VCPKG_ROOT": "PATH/TO/VCPKG"
      }
    }
  ]
}
```
Then run:
```cmd
cmake --preset default
```
to build the CMake __cache__.  

And finally:
```cmd
mkdir build
cmake --build .\build\
```
to __build__ the project. The *.exe* file can be found in `build/Debug/UnknownEngine.exe`.

