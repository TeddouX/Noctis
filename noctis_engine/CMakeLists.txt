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
    "include/noctis/asset/asset_manager.hpp"
    "include/noctis/asset/asset.hpp"

    "include/noctis/ecs/component/actor_component.hpp"
    "include/noctis/ecs/component/component_registry.hpp"
    "include/noctis/ecs/component/component_registry.inl"
    "include/noctis/ecs/component/component.hpp"
    "include/noctis/ecs/component/component.inl"
    "include/noctis/ecs/component/light_component.hpp"
    "include/noctis/ecs/component/material_component.hpp"
    "include/noctis/ecs/component/model_component.hpp"
    "include/noctis/ecs/component/script_component.hpp"
    "include/noctis/ecs/component/transform_component.hpp"

    "include/noctis/ecs/system/lighting_system.hpp"
    "include/noctis/ecs/system/lighting_system.inl"
    "include/noctis/ecs/system/render_system.hpp"
    "include/noctis/ecs/system/scripting_system.hpp"
    "include/noctis/ecs/system/system.hpp"
    "include/noctis/ecs/system/systems_manager.hpp"
    "include/noctis/ecs/system/systems_manager.inl"

    "include/noctis/ecs/component_array.hpp"
    "include/noctis/ecs/component_array.inl"
    "include/noctis/ecs/component_manager.hpp"
    "include/noctis/ecs/component_manager.inl"
    "include/noctis/ecs/entity.hpp"
 
    "include/noctis/math/color.hpp"
    "include/noctis/math/math.hpp"

    "include/noctis/property/asset_property.hpp"
    "include/noctis/property/color_property.hpp"
    "include/noctis/property/float_property.hpp"
    "include/noctis/property/int_property.hpp"
    "include/noctis/property/property.hpp"
    "include/noctis/property/string_property.hpp"
    "include/noctis/property/vec3_property.hpp"

    "include/noctis/rendering/camera.hpp"
    "include/noctis/rendering/framebuffer.hpp"
    "include/noctis/rendering/material.hpp"
    "include/noctis/rendering/mesh.hpp"
    "include/noctis/rendering/model.hpp"
    "include/noctis/rendering/shader.hpp"
    "include/noctis/rendering/ssbo.hpp"
    "include/noctis/rendering/ssbo.inl"
    "include/noctis/rendering/texture.hpp"
    "include/noctis/rendering/vertex.hpp"

    "include/noctis/scene/scene_manager.hpp"
    "include/noctis/scene/scene.hpp"
    "include/noctis/scene/scene.inl"

    "include/noctis/scripting/engine_bindings.hpp"
    "include/noctis/scripting/script_builder.hpp"

    "include/noctis/utils/uuid.hpp"

    "include/noctis/engine.hpp"
    "include/noctis/filesystem.hpp"
    "include/noctis/logger.hpp"
    "include/noctis/logger.inl"
    "include/noctis/window.hpp"

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
        "include/noctis"
)
