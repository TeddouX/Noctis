#pragma once


#if defined(_WIN32) || defined(_WIN64)
    // Disable warning from using STL 
    // member variables in classes
    #pragma warning(disable : 4251)
    
    #ifdef UNE_ENGINE_BUILD
        #define UNE_API __declspec(dllexport)
    #else
        #define UNE_API __declspec(dllimport)
    #endif
#else
    #define UNE_API
#endif