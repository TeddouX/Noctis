cmake_minimum_required(VERSION 3.10)
project(Noctis)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (NOT WIN32)
    message(FATAL_ERROR "This project currently only supports Windows.\n")
endif()

if (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
endif()

add_subdirectory(thirdparty/as_addons)
add_subdirectory(noctis_engine)
add_subdirectory(noctis_editor)
# add_subdirectory(uke_runtime)
