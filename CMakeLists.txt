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

add_definitions(-D GLM_ENABLE_EXPERIMENTAL)

add_executable(UnknownEngine 
    src/main.cpp

	src/core/logger.hpp
	src/core/logger.cpp
	src/core/manager.hpp
	src/core/manager.cpp
	src/core/window.hpp
	src/core/window.cpp
	src/core/stb_image_impl.c
	src/core/ecs/all_components.hpp
	src/core/ecs/component_array.hpp
	src/core/ecs/component_manager.hpp
	src/core/ecs/entity.hpp
	src/core/ecs/systems/render_system.cpp
	src/core/ecs/systems/render_system.hpp
	src/core/ecs/systems/system.hpp

    src/editor/editor_ui.hpp
    src/editor/editor_ui.cpp
	src/editor/widgets/widget.hpp
	src/editor/widgets/actor_properties.hpp
	src/editor/widgets/actor_properties.cpp
	src/editor/widgets/asset_explorer.hpp
	src/editor/widgets/asset_explorer.cpp
	src/editor/widgets/console_widget.hpp
	src/editor/widgets/console_widget.cpp
	src/editor/widgets/scene_display.hpp
	src/editor/widgets/scene_display.cpp
	src/editor/widgets/scene_tree.hpp
	src/editor/widgets/scene_tree.cpp


	src/loading/model_loader.hpp
	src/loading/model_loader.cpp
	
	src/rendering/camera.hpp
	src/rendering/camera.cpp
	src/rendering/framebuffer.hpp
	src/rendering/framebuffer.cpp
	src/rendering/mesh.hpp
	src/rendering/mesh.cpp
	src/rendering/model.hpp
	src/rendering/model.cpp
	src/rendering/renderer.hpp
	src/rendering/renderer.cpp
	src/rendering/shader.hpp
	src/rendering/shader.cpp
	src/rendering/texture.hpp
	src/rendering/texture.cpp
	src/rendering/vertex.hpp	
)

target_include_directories(UnknownEngine PRIVATE ${Stb_INCLUDE_DIR})

target_link_libraries(UnknownEngine PRIVATE
	assimp::assimp
	imgui::imgui
	glad::glad
	glm::glm
	glfw
)
