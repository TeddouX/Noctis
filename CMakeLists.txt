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

# if(MSVC)
#     add_compile_options(/showIncludes)
# endif()

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT UnknownEngine)

add_executable(UnknownEngine 
	src/core/asset_manager.hpp
	src/core/imgui_utils.hpp
	src/core/logger.hpp
	src/core/logger.inl
	src/core/project.hpp
	src/core/window.hpp
	src/core/scene/actor_creation_helper.hpp
	src/core/scene/scene.hpp
	src/core/scene/scene.inl
	src/core/scene/scene_manager.hpp
	src/core/ecs/component_array.hpp
	src/core/ecs/component_array.inl
	src/core/ecs/component_manager.hpp
	src/core/ecs/component_manager.inl
	src/core/ecs/entity.hpp
	src/core/ecs/component/actor.hpp
	src/core/ecs/component/all_components.hpp
	src/core/ecs/component/material.hpp
	src/core/ecs/component/model_component.hpp
	src/core/ecs/component/property.hpp
	src/core/ecs/component/property.inl
	src/core/ecs/component/transform.hpp
	src/core/ecs/system/render_system.hpp
	src/core/ecs/system/system.hpp
	src/core/ecs/system/systems_manager.hpp
	src/core/ecs/system/systems_manager.inl
	src/core/math/math.hpp

    src/editor/editor_ui.hpp
	src/editor/widget/widget.hpp
	src/editor/widget/actor_properties.hpp
	src/editor/widget/asset_explorer.hpp
	src/editor/widget/console.hpp
	src/editor/widget/scene_display.hpp
	src/editor/widget/scene_tree.hpp
	
	src/rendering/camera.hpp
	src/rendering/framebuffer.hpp
	src/rendering/mesh.hpp
	src/rendering/model.hpp
	src/rendering/shader.hpp
	src/rendering/texture.hpp
	src/rendering/vertex.hpp	
)

target_sources(UnknownEngine PRIVATE
    src/main.cpp

	src/core/asset_manager.cpp
	src/core/imgui_utils.cpp
	src/core/logger.cpp
	src/core/project.cpp
	src/core/stb_image_impl.c
	src/core/window.cpp
	src/core/scene/actor_creation_helper.cpp
	src/core/scene/scene.cpp
	src/core/scene/scene_manager.cpp
	src/core/ecs/component_manager.cpp
	src/core/ecs/component/actor.cpp
	src/core/ecs/component/transform.cpp
	src/core/ecs/system/render_system.cpp
	src/core/ecs/system/systems_manager.cpp
	src/core/math/math.cpp

    src/editor/editor_ui.cpp
	src/editor/widget/actor_properties.cpp
	src/editor/widget/asset_explorer.cpp
	src/editor/widget/console.cpp
	src/editor/widget/scene_display.cpp
	src/editor/widget/scene_tree.cpp

	src/rendering/camera.cpp
	src/rendering/framebuffer.cpp
	src/rendering/mesh.cpp
	src/rendering/model.cpp
	src/rendering/shader.cpp
	src/rendering/texture.cpp
)

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
