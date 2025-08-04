cmake_minimum_required(VERSION 3.10)
project(UnknownEngine)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (NOT WIN32)
    message(FATAL_ERROR "This project currently only supports Windows.\n")
endif()

add_subdirectory(thirdparty/as_addons)
add_subdirectory(une_engine)
add_subdirectory(une_editor)
# add_subdirectory(uke_runtime)
