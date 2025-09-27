project(NoctisTesting)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(NoctisTesting "main.cpp")
target_link_libraries(NoctisTesting NoctisEngine)

add_custom_target(copy_engine_dll ALL
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:NoctisEngine>
        $<TARGET_FILE_DIR:NoctisTesting>
    DEPENDS NoctisEngine
)
