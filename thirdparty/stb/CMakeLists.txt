cmake_minimum_required(VERSION 3.10)
project(Stb)

add_library(Stb STATIC
    "include/stb_image.h"
    "include/stb_image_write.h"

    "src/stb_image_impl.c"
    "src/stb_image_write_impl.c"
)

target_include_directories(Stb PUBLIC "include")
