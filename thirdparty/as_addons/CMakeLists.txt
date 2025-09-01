cmake_minimum_required(VERSION 3.10)
project(as_addons)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(AS_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include/angelscript")

set(ANGELSCRIPT_ADDONS_SOURCE
    "${AS_INCLUDE_DIR}/autowrapper/aswrappedcall.h"

    "${AS_INCLUDE_DIR}/contextmgr/contextmgr.h"
    "${AS_INCLUDE_DIR}/contextmgr/contextmgr.cpp"

    "${AS_INCLUDE_DIR}/datetime/datetime.h"
    "${AS_INCLUDE_DIR}/datetime/datetime.cpp"

    "${AS_INCLUDE_DIR}/debugger/debugger.h"
    "${AS_INCLUDE_DIR}/debugger/debugger.cpp"

    "${AS_INCLUDE_DIR}/scriptany/scriptany.h"
    "${AS_INCLUDE_DIR}/scriptany/scriptany.cpp"

    "${AS_INCLUDE_DIR}/scriptarray/scriptarray.h"
    "${AS_INCLUDE_DIR}/scriptarray/scriptarray.cpp"

    "${AS_INCLUDE_DIR}/scriptbuilder/scriptbuilder.h"
    "${AS_INCLUDE_DIR}/scriptbuilder/scriptbuilder.cpp"

    "${AS_INCLUDE_DIR}/scriptdictionary/scriptdictionary.h"
    "${AS_INCLUDE_DIR}/scriptdictionary/scriptdictionary.cpp"

    "${AS_INCLUDE_DIR}/scriptfile/scriptfile.h"
    "${AS_INCLUDE_DIR}/scriptfile/scriptfile.cpp"
    "${AS_INCLUDE_DIR}/scriptfile/scriptfilesystem.h"
    "${AS_INCLUDE_DIR}/scriptfile/scriptfilesystem.cpp"

    "${AS_INCLUDE_DIR}/scripthandle/scripthandle.h"
    "${AS_INCLUDE_DIR}/scripthandle/scripthandle.cpp"

    "${AS_INCLUDE_DIR}/scripthelper/scripthelper.h"
    "${AS_INCLUDE_DIR}/scripthelper/scripthelper.cpp"

    "${AS_INCLUDE_DIR}/scriptmath/scriptmath.h"
    "${AS_INCLUDE_DIR}/scriptmath/scriptmath.cpp"
    "${AS_INCLUDE_DIR}/scriptmath/scriptmathcomplex.h"
    "${AS_INCLUDE_DIR}/scriptmath/scriptmathcomplex.cpp"

    "${AS_INCLUDE_DIR}/scriptstdstring/scriptstdstring.h"
    "${AS_INCLUDE_DIR}/scriptstdstring/scriptstdstring.cpp"
    "${AS_INCLUDE_DIR}/scriptstdstring/scriptstdstring_utils.cpp"

    "${AS_INCLUDE_DIR}/serializer/serializer.h"
    "${AS_INCLUDE_DIR}/serializer/serializer.cpp"

    "${AS_INCLUDE_DIR}/weakref/weakref.h"
    "${AS_INCLUDE_DIR}/weakref/weakref.cpp"

    "${AS_INCLUDE_DIR}/angelscript.h"
)

source_group(TREE ${AS_INCLUDE_DIR} FILES ${ANGELSCRIPT_ADDONS_SOURCE})

add_library(as_addons ${ANGELSCRIPT_ADDONS_SOURCE})

target_include_directories(as_addons PUBLIC ${AS_INCLUDE_DIR})
