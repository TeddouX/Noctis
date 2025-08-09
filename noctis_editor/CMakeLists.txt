project(NoctisEditor)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(imgui CONFIG REQUIRED)

set(EDITOR_SOURCES 
    # -------------------
    #      Headers
    # -------------------
    "include/editor/ui/widget/actor_properties.hpp"
    "include/editor/ui/widget/asset_explorer.hpp"
    "include/editor/ui/widget/console.hpp"
    "include/editor/ui/widget/scene_display.hpp"
    "include/editor/ui/widget/scene_tree.hpp"
    "include/editor/ui/widget/widget.hpp"

    "include/editor/ui/editor_ui.hpp"
    "include/editor/ui/project_selection.hpp"

    "include/editor/utils/actor_creation_helper.hpp"
    "include/editor/utils/imgui_utils.hpp"
    "include/editor/utils/property_rendering.hpp"

    "include/editor/editor.hpp"
    "include/editor/project.hpp"

    # -------------------
    #    Source files
    # -------------------
    "src/ui/widget/actor_properties.cpp"
    "src/ui/widget/asset_explorer.cpp"
    "src/ui/widget/console.cpp"
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

    add_custom_command(TARGET NoctisEditor POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:NoctisEngine>
            $<TARGET_PDB_FILE:NoctisEngine>
            $<TARGET_RUNTIME_DLLS:NoctisEngine>
            $<TARGET_FILE_DIR:NoctisEditor>
        COMMAND_EXPAND_LISTS
    )
endif()

target_link_libraries(NoctisEditor PRIVATE 
    imgui::imgui
    NoctisEngine
)

target_include_directories(NoctisEditor 
    PUBLIC "include"
    PRIVATE "include/editor"
)
