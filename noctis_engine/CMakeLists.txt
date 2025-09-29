project(NoctisEngine)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  glfw
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG        3.3.9
)

set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(glfw)

set(ENGINE_SOURCES
    # -------------------
    #      Headers
    # -------------------
    "include/noctis/rendering/opengl/ogl_ctx.hpp"
    "include/noctis/rendering/opengl/ogl_shader.hpp"
    "include/noctis/rendering/opengl/ogl_ssbo.hpp"
    "include/noctis/rendering/opengl/ogl_uniform_buffer.hpp"
    "include/noctis/rendering/opengl/ogl_vertex_array.hpp"
    
    "include/noctis/rendering/camera.hpp"
    "include/noctis/rendering/graphics_backend_ctx.hpp"
    "include/noctis/rendering/shader.hpp"
    "include/noctis/rendering/ssbo.hpp"
    "include/noctis/rendering/uniform_buffer.hpp"
    "include/noctis/rendering/vertex_array.hpp"

    "include/noctis/window/window.hpp"
    
    "include/noctis/engine.hpp"

    # -------------------
    #    Source files
    # -------------------
    "src/rendering/opengl/ogl_ctx.cpp"
    "src/rendering/opengl/ogl_shader.cpp"
    "src/rendering/opengl/ogl_ssbo.cpp"
    "src/rendering/opengl/ogl_uniform_buffer.cpp"
    "src/rendering/opengl/ogl_vertex_array.cpp"
    
    "src/rendering/camera.cpp"
    "src/rendering/shader.cpp"
    "src/rendering/ssbo.cpp"
    "src/rendering/uniform_buffer.cpp"
    "src/rendering/vertex_array.cpp"

    "src/window/window.cpp"
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${ENGINE_SOURCES})

add_library(NoctisEngine SHARED ${ENGINE_SOURCES})

target_compile_definitions(NoctisEngine 
    PUBLIC 
        GLM_ENABLE_EXPERIMENTAL
    PRIVATE
        NOCTIS_BUILD
)

target_link_libraries(NoctisEngine PUBLIC
    glm::glm
	glfw
    Glad
)

target_include_directories(NoctisEngine 
    PUBLIC 
        "include"
    PRIVATE 
        "include/noctis"
)
