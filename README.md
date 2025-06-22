
# Unknown Engine: a simplistic game engine

/!\ In developement

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
cmake --build .\build\
```
to __build__ the project. The *.exe* file can be found in `build/Debug/UnknownEngine.exe`.

