project(UNE_Engine)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(nlohmann_json CONFIG REQUIRED)
find_package(assimp CONFIG REQUIRED)
find_package(glfw3  CONFIG REQUIRED)
find_package(glad   CONFIG REQUIRED)
find_package(fmt    CONFIG REQUIRED)
find_package(glm    CONFIG REQUIRED)
find_package(stb    REQUIRED)


file(GLOB ENGINE_MAIN          "src/*.cpp" "src/*.c" "include/engine/*.hpp")
file(GLOB ENGINE_ECS           "src/ecs/*.cpp" "include/engine/ecs/*.hpp")
file(GLOB ENGINE_ECS_COMPONENT "src/ecs/component/*.cpp" "include/engine/ecs/component/*.hpp")
file(GLOB ENGINE_ECS_SYSTEM    "src/ecs/system/*.cpp" "include/engine/ecs/system/*.hpp")
file(GLOB ENGINE_MATH          "src/math/*.cpp" "include/engine/math/*.hpp")
file(GLOB ENGINE_RENDERING     "src/rendering/*.cpp" "include/engine/rendering/*.hpp")
file(GLOB ENGINE_SCENE         "src/scene/*.cpp" "include/engine/scene/*.hpp")
file(GLOB ENGINE_UTILS         "src/utils/*.cpp" "src/*.c" "include/engine/utils/*.hpp")


set(ENGINE_SOURCES 
    ${ENGINE_MAIN} 
    ${ENGINE_ECS}
    ${ENGINE_ECS_COMPONENT}
    ${ENGINE_ECS_SYSTEM}
    ${ENGINE_MATH}
    ${ENGINE_RENDERING}
    ${ENGINE_SCENE}
    ${ENGINE_UTILS}
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${ENGINE_SOURCES})

add_library(UNE_Engine ${ENGINE_SOURCES})

target_compile_definitions(UNE_Engine PUBLIC GLM_ENABLE_EXPERIMENTAL)

target_link_libraries(UNE_Engine PUBLIC
	nlohmann_json::nlohmann_json	
	assimp::assimp
	glad::glad
	glm::glm
	fmt::fmt
	glfw
)

target_include_directories(UNE_Engine 
    PUBLIC "include"
    PRIVATE "include/engine"
)