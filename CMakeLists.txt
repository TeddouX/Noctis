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

add_executable(UnknownEngine 
	src/core/logger.hpp
	src/core/logger.inl
	src/core/project.hpp
	src/core/window.hpp
	src/core/scene/scene.hpp
	src/core/scene/scene.inl
	src/core/scene/scene_manager.hpp
	src/core/ecs/all_components.hpp
	src/core/ecs/component_array.hpp
	src/core/ecs/component_array.inl
	src/core/ecs/component_manager.hpp
	src/core/ecs/component_manager.inl
	src/core/ecs/entity.hpp
	src/core/ecs/systems/render_system.hpp
	src/core/ecs/systems/system.hpp
	src/core/ecs/systems/systems_manager.hpp
	src/core/ecs/systems/systems_manager.inl

    src/editor/editor_ui.hpp
	src/editor/widgets/widget.hpp
	src/editor/widgets/actor_properties.hpp
	src/editor/widgets/asset_explorer.hpp
	src/editor/widgets/console_widget.hpp
	src/editor/widgets/scene_display.hpp
	src/editor/widgets/scene_tree.hpp

	src/loading/model_loader.hpp
	
	src/rendering/camera.hpp
	src/rendering/framebuffer.hpp
	src/rendering/mesh.hpp
	src/rendering/model.hpp
	src/rendering/renderer.hpp
	src/rendering/shader.hpp
	src/rendering/texture.hpp
	src/rendering/vertex.hpp	
)

target_sources(UnknownEngine PRIVATE
    src/main.cpp

	src/core/logger.cpp
	src/core/project.cpp
	src/core/stb_image_impl.c
	src/core/window.cpp
	src/core/scene/scene.cpp
	src/core/scene/scene_manager.cpp
	src/core/ecs/systems/render_system.cpp
	src/core/ecs/systems/systems_manager.cpp

    src/editor/editor_ui.cpp
	src/editor/widgets/actor_properties.cpp
	src/editor/widgets/asset_explorer.cpp
	src/editor/widgets/console_widget.cpp
	src/editor/widgets/scene_display.cpp
	src/editor/widgets/scene_tree.cpp

	src/loading/model_loader.cpp

	src/rendering/camera.cpp
	src/rendering/framebuffer.cpp
	src/rendering/mesh.cpp
	src/rendering/model.cpp
	src/rendering/renderer.cpp
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
