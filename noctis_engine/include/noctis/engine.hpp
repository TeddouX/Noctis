#pragma once

#define NOCTIS_OPENGL_VERSION "#version 460 core"

#if defined(_WIN32) || defined(_WIN64)
    // Disable warning from using STL 
    // member variables in classes
    #pragma warning(disable : 4251)
    
    #ifdef NOCTIS_BUILD
        #define NOCTIS_API __declspec(dllexport)
    #else
        #define NOCTIS_API __declspec(dllimport)
    #endif
#else
    #define NOCTIS_API
#endif