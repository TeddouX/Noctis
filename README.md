# Noctis: a simplistic game engine  
/!\ In developement  
Linux and MacOS support will be added in the late future.  
A public [Trello board](https://trello.com/b/By0OcR3N/noctis) is available for anyone to see. If you have an ideas for a feature, feel free to create a GitHub [issue](https://github.com/TeddouX/Noctis/issues/new) with the __enhancement__ label.  

### Editor
The editor's UI is made using [ImGui](https://github.com/ocornut/imgui).  
  
<img width="1920" height="1080" alt="Screenshot of Uknown Engine's editor's UI" src="https://github.com/user-attachments/assets/0673b0fa-722e-4579-9e54-8539cd8fa626" />

### Build locally

__[vcpkg](https://vcpkg.io/en/) and [CMake](https://cmake.org/) are required.__  
For __vcpkg__, follow the installation guide on: [Microsoft Learn](https://learn.microsoft.com/en-us/vcpkg/get_started/get-started?pivots=shell-powershell#1---set-up-vcpkg). For this project, following the tutorial past step one is not necessary.  

After installing vcpkg and CMake, you will need to create a file named __`CMakeUserPresets.json`__ in the root of the cloned repository containing this:  
```json
{
  "version": 3,
  "configurePresets": [
    {
      "name": "default",
      "inherits": "vcpkg",
      "environment": {
        "VCPKG_ROOT": "F:/PATH/TO/VCPKG",
        "VCPKG_DEFAULT_TRIPLET": "HOST TRIPLET"
      }
    }
  ]
} 
```  
Replace `"PATH/TO/VCPKG"` with the path to the vcpkg installation and `"VCPKG_DEFAULT_TRIPLET"` with x64-window for 64-bit windows and x32-windows for 32 bit windows, depending on your installation. 

Then run:
```cmd
cmake --preset default
```
to build the CMake cache and install required __vcpkg__ libraries, this might take some time.  

And finally:
```cmd
mkdir build
cmake --build .\build\
```
to build the project.

### Credits
- [Assimp](https://github.com/assimp/assimp) - The official Open-Asset-Importer-Library
- [Glfw3](https://github.com/glfw/glfw) - A multi-platform library for OpenGL, OpenGL ES, Vulkan, window and input
- [GLM](https://github.com/g-truc/glm) - OpenGL Mathematics
- [Dear ImGui](https://github.com/ocornut/imgui) - Bloat-free Graphical User interface for C++ with minimal dependencies
- [STB](https://github.com/nothings/stb) - Single-file public domain libraries for C/C++ (*Noctis uses [stb_image.h](https://github.com/nothings/stb/blob/master/stb_image.h) for image loading*).
- [Glad](https://github.com/Dav1dde/glad) - Multi-Language Vulkan/GL/GLES/EGL/GLX/WGL Loader-Generator based on the official specs. Use [this](https://gen.glad.sh/) to generate a loader.
- [Nlohmann-json](https://github.com/nlohmann/json) - JSON for Modern C++
- [Fmt](https://github.com/fmtlib/fmt) - A modern formatting library
- [AngelScript](https://www.angelcode.com/angelscript/) - An extremely flexible cross-platform scripting library  