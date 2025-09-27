cmake_minimum_required(VERSION 3.10)
project(Noctis)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(thirdparty/glad)
add_subdirectory(thirdparty/glm)

add_subdirectory(noctis_engine)
add_subdirectory(noctis_testing)
