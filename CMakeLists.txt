cmake_minimum_required(VERSION 3.23)
project(Rusty LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (MSVC)
    # warning level 4
    add_compile_options(/W4)
else ()
    # additional warnings
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()


add_subdirectory(src)
add_subdirectory(tests)
