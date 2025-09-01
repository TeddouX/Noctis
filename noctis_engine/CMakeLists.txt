project(NoctisEngine)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(nlohmann_json CONFIG REQUIRED)
find_package(Angelscript   CONFIG REQUIRED)
find_package(glfw3         CONFIG REQUIRED)
find_package(fmt           CONFIG REQUIRED)
find_package(glm           CONFIG REQUIRED)

set(ENGINE_SOURCES
    # -------------------
    #      Headers
    # -------------------
    "include/engine/asset/asset_manager.hpp"
    "include/engine/asset/asset.hpp"

    "include/engine/ecs/component/actor_component.hpp"
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

    "include/engine/property/asset_property.hpp"
    "include/engine/property/color_property.hpp"
    "include/engine/property/float_property.hpp"
    "include/engine/property/int_property.hpp"
    "include/engine/property/property.hpp"
    "include/engine/property/string_property.hpp"
    "include/engine/property/vec3_property.hpp"

    "include/engine/rendering/camera.hpp"
    "include/engine/rendering/framebuffer.hpp"
    "include/engine/rendering/material.hpp"
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

    "include/engine/scripting/engine_bindings.hpp"
    "include/engine/scripting/script_builder.hpp"

    "include/engine/utils/uuid.hpp"

    "include/engine/engine.hpp"
    "include/engine/filesystem.hpp"
    "include/engine/logger.hpp"
    "include/engine/logger.inl"
    "include/engine/window.hpp"

    # -------------------
    #    Source files
    # -------------------
    "src/asset/asset_manager.cpp"
    
    "src/ecs/component/actor_component.cpp"
    "src/ecs/component/component_registry.cpp"
    "src/ecs/component/component.cpp"
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

    "src/scripting/engine_bindings.cpp"
    "src/scripting/script_builder.cpp"

    "src/utils/uuid.cpp"

    "src/filesystem.cpp"
    "src/logger.cpp"
    "src/window.cpp"
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
	nlohmann_json::nlohmann_json
    Angelscript::angelscript
	glm::glm
	fmt::fmt

	glfw
    as_addons
    Glad
)

target_include_directories(NoctisEngine 
    PUBLIC 
        "include"
    PRIVATE 
        "include/engine"
)
