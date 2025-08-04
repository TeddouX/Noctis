cmake_minimum_required(VERSION 3.10)
project(as_addons)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    # 64 bits win
    set(HOST_TRIPLET "x64-windows")
elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
    # 32 bits win
    set(HOST_TRIPLET "x32-windows")
endif()


set(VCPKG_INCLUDE_DIR ${VCPKG_INSTALLED_DIR}/${HOST_TRIPLET}/include)
set(AS_INCLUDE_DIR ${VCPKG_INCLUDE_DIR}/angelscript)

file(GLOB_RECURSE ANGELSCRIPT_SOURCE
    "${AS_INCLUDE_DIR}/*.cpp"
    "${AS_INCLUDE_DIR}/*.h"
    ${VCPKG_INCLUDE_DIR}/angelscript.h
)

source_group("AS Addons Source" FILES ${ANGELSCRIPT_SOURCE})

add_library(as_addons STATIC ${ANGELSCRIPT_SOURCE})

# angelscript.h
target_include_directories(as_addons PUBLIC ${VCPKG_INCLUDE_DIR})
# AngelScript addons
target_include_directories(as_addons PUBLIC ${AS_INCLUDE_DIR})
