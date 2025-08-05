project(UNE_Engine)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(nlohmann_json CONFIG REQUIRED)
find_package(Angelscript   CONFIG REQUIRED)
find_package(assimp        CONFIG REQUIRED)
find_package(glfw3         CONFIG REQUIRED)
find_package(glad          CONFIG REQUIRED)
find_package(fmt           CONFIG REQUIRED)
find_package(glm           CONFIG REQUIRED)
find_package(Stb                  REQUIRED)


set(ENGINE_SOURCES
    # -------------------
    #      Headers
    # -------------------
    "include/engine/ecs/component/property/all_properties.hpp"
    "include/engine/ecs/component/property/color_property.hpp"
    "include/engine/ecs/component/property/float_property.hpp"
    "include/engine/ecs/component/property/int_property.hpp"
    "include/engine/ecs/component/property/model_property.hpp"
    "include/engine/ecs/component/property/property.hpp"
    "include/engine/ecs/component/property/shader_property.hpp"
    "include/engine/ecs/component/property/string_property.hpp"
    "include/engine/ecs/component/property/vec3_property.hpp"

    "include/engine/ecs/component/actor_component.hpp"
    "include/engine/ecs/component/all_components.hpp"
    "include/engine/ecs/component/component_registry.hpp"
    "include/engine/ecs/component/component_registry.inl"
    "include/engine/ecs/component/component.hpp"
    "include/engine/ecs/component/component.inl"
    "include/engine/ecs/component/light_component.hpp"
    "include/engine/ecs/component/material_component.hpp"
    "include/engine/ecs/component/model_component.hpp"
    "include/engine/ecs/component/script_component.hpp"
    "include/engine/ecs/component/transform_component.hpp"

    "include/engine/ecs/system/lighting_system.hpp"
    "include/engine/ecs/system/lighting_system.inl"
    "include/engine/ecs/system/render_system.hpp"
    "include/engine/ecs/system/scripting_system.hpp"
    "include/engine/ecs/system/system.hpp"
    "include/engine/ecs/system/systems_manager.hpp"
    "include/engine/ecs/system/systems_manager.inl"

    "include/engine/ecs/component_array.hpp"
    "include/engine/ecs/component_array.inl"
    "include/engine/ecs/component_manager.hpp"
    "include/engine/ecs/component_manager.inl"
    "include/engine/ecs/entity.hpp"
 
    "include/engine/math/color.hpp"
    "include/engine/math/math.hpp"

    "include/engine/rendering/camera.hpp"
    "include/engine/rendering/framebuffer.hpp"
    "include/engine/rendering/mesh.hpp"
    "include/engine/rendering/model.hpp"
    "include/engine/rendering/shader.hpp"
    "include/engine/rendering/ssbo.hpp"
    "include/engine/rendering/ssbo.inl"
    "include/engine/rendering/texture.hpp"
    "include/engine/rendering/vertex.hpp"

    "include/engine/scene/scene_manager.hpp"
    "include/engine/scene/scene.hpp"
    "include/engine/scene/scene.inl"

    "include/engine/utils/uuid.hpp"

    "include/engine/asset_manager.hpp"
    "include/engine/filesystem.hpp"
    "include/engine/logger.hpp"
    "include/engine/logger.inl"
    "include/engine/window.hpp"

    # -------------------
    #    Source files
    # -------------------
    "src/ecs/component/actor_component.cpp"
    "src/ecs/component/component_registry.cpp"
    "src/ecs/component/light_component.cpp"
    "src/ecs/component/material_component.cpp"
    "src/ecs/component/model_component.cpp"
    "src/ecs/component/script_component.cpp"
    "src/ecs/component/transform_component.cpp"

    "src/ecs/system/lighting_system.cpp"
    "src/ecs/system/render_system.cpp"
    "src/ecs/system/scripting_system.cpp"
    "src/ecs/system/systems_manager.cpp"

    "src/ecs/component_manager.cpp"

    "src/math/color.cpp"
    "src/math/math.cpp"

    "src/rendering/camera.cpp"
    "src/rendering/framebuffer.cpp"
    "src/rendering/mesh.cpp"
    "src/rendering/model.cpp"
    "src/rendering/shader.cpp"
    "src/rendering/texture.cpp"

    "src/scene/scene_manager.cpp"
    "src/scene/scene.cpp"

    "src/utils/uuid.cpp"

    "src/asset_manager.cpp"
    "src/filesystem.cpp"
    "src/logger.cpp"
    "src/stb_image_impl.c"
    "src/window.cpp"
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${ENGINE_SOURCES})

add_library(UNE_Engine ${ENGINE_SOURCES})

target_compile_definitions(UNE_Engine PUBLIC GLM_ENABLE_EXPERIMENTAL)

target_link_libraries(UNE_Engine PUBLIC
	nlohmann_json::nlohmann_json
    Angelscript::angelscript
	assimp::assimp
	glad::glad
	glm::glm
	fmt::fmt
	glfw
    as_addons
)

target_include_directories(UNE_Engine 
    PUBLIC "include"
    PRIVATE "include/engine"
)