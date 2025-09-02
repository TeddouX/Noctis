project(NoctisEditor)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(assimp CONFIG REQUIRED)
find_package(imgui  CONFIG REQUIRED)

set(EDITOR_SOURCES 
    # -------------------
    #      Headers
    # -------------------
    "src/asset_management/asset/asset.hpp"
    "src/asset_management/asset/material_asset.hpp"
    "src/asset_management/asset/model_asset.hpp"
    "src/asset_management/asset/script_asset.hpp"
    "src/asset_management/asset/shader_asset.hpp"
    "src/asset_management/asset/texture_asset.hpp"
    "src/asset_management/importer/model_importer.hpp"
    "src/asset_management/importer/texture_importer.hpp"
    "src/asset_management/editor_asset_manager.hpp"

    "src/ui/widget/asset_explorer.hpp"
    "src/ui/widget/console.hpp"
    "src/ui/widget/properties.hpp"
    "src/ui/widget/scene_display.hpp"
    "src/ui/widget/scene_tree.hpp"
    "src/ui/widget/widget.hpp"

    "src/ui/editor_ui.hpp"
    "src/ui/project_selection.hpp"

    "src/utils/actor_creation_helper.hpp"
    "src/utils/imgui_utils.hpp"
    "src/utils/property_rendering.hpp"

    "src/editor.hpp"
    "src/project.hpp"

    # -------------------
    #    Source files
    # -------------------
    "src/asset_management/importer/model_importer.cpp"
    "src/asset_management/importer/texture_importer.cpp"
    "src/asset_management/editor_asset_manager.cpp"

    "src/ui/widget/asset_explorer.cpp"
    "src/ui/widget/console.cpp"
    "src/ui/widget/properties.cpp"
    "src/ui/widget/scene_display.cpp"
    "src/ui/widget/scene_tree.cpp"

    "src/ui/editor_ui.cpp"
    "src/ui/project_selection.cpp"
    
    "src/utils/actor_creation_helper.cpp"
    "src/utils/imgui_utils.cpp"
    "src/utils/property_rendering.cpp"
    
    "src/editor_main.cpp"
    "src/editor.cpp"
    "src/project.cpp"
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${EDITOR_SOURCES})

add_executable(NoctisEditor ${EDITOR_SOURCES})

if (MSVC)
    # Set visual studio CWD
    set_target_properties(NoctisEditor PROPERTIES
        VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    )

    # Set the editor as the startup directory
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY 
        VS_STARTUP_PROJECT NoctisEditor
    )
endif()

target_link_libraries(NoctisEditor PRIVATE 
    assimp::assimp
    imgui::imgui

    NoctisEngine
    Stb
)

target_include_directories(NoctisEditor 
    PUBLIC 
        "include"
    PRIVATE 
        "include/editor"
        ${Stb_INCLUDE_DIR}
)

add_custom_command(TARGET NoctisEditor POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:NoctisEngine>
        $<TARGET_FILE_DIR:NoctisEditor>
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_RUNTIME_DLLS:NoctisEngine>
        $<TARGET_FILE_DIR:NoctisEditor>
    COMMAND_EXPAND_LISTS
)
