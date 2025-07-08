cmake_minimum_required(VERSION 3.10)
project(UnknownEngine)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(assimp CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(stb REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)

add_definitions(-D GLM_ENABLE_EXPERIMENTAL)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT UnknownEngine)

file(GLOB_RECURSE MAIN "src/main.cpp")
file(GLOB_RECURSE RENDERING "src/rendering/*.cpp" "src/rendering/*.hpp")
file(GLOB_RECURSE EDITOR "src/editor/*.cpp" "src/editor/*.hpp")
file(GLOB_RECURSE EDITOR_WIDGETS "src/editor/widget/*.cpp" "src/editor/widget/*.hpp")
file(GLOB_RECURSE CORE "src/core/*.cpp" "src/core/*.c" "src/core/*.hpp" "src/core/*.inl")
file(GLOB_RECURSE CORE_SCENE "src/core/scene/*.cpp" "src/core/scene/*.hpp" "src/core/scene/*.inl")
file(GLOB_RECURSE CORE_MATH "src/core/math/*.cpp" "src/core/math/*.hpp")
file(GLOB_RECURSE CORE_ECS "src/core/ecs/*.cpp" "src/core/ecs/*.hpp")
file(GLOB_RECURSE CORE_ECS_SYSTEM "src/core/ecs/system/*.cpp" "src/core/ecs/system/*.hpp")
file(GLOB_RECURSE CORE_ECS_COMPONENT "src/core/ecs/component/*.cpp" "src/core/ecs/component/*.hpp")

set(ALL_SOURCES 
	${MAIN}
	${RENDERING}
	${EDITOR}
	${EDITOR_WIDGETS}
	${CORE}
	${CORE_SCENE}
	${CORE_MATH}
	${CORE_ECS}
	${CORE_ECS_SYSTEM}
	${CORE_ECS_COMPONENT}
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${ALL_SOURCES})

add_executable(UnknownEngine ${ALL_SOURCES})

target_include_directories(UnknownEngine PRIVATE ${Stb_INCLUDE_DIR})

target_link_libraries(UnknownEngine PRIVATE
	nlohmann_json::nlohmann_json	
	assimp::assimp
	imgui::imgui
	glad::glad
	glm::glm
	fmt::fmt
	glfw
)
