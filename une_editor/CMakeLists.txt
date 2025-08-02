project(UNE_Editor)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(imgui CONFIG REQUIRED)

file(GLOB EDITOR_MAIN   "src/*.cpp" "include/editor/*.hpp")
file(GLOB EDITOR_WIDGET "src/widget/*.cpp" "include/editor/widget/*.hpp")

set(EDITOR_SOURCES ${EDITOR_MAIN} ${EDITOR_WIDGET})

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${EDITOR_SOURCES})

add_executable(UNE_Editor ${EDITOR_SOURCES})
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

target_link_libraries(UNE_Editor PRIVATE 
    imgui::imgui
    UNE_Engine
)

target_include_directories(UNE_Editor 
    PUBLIC "include"
    PRIVATE "include/editor"
)
