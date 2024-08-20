cmake_minimum_required(VERSION 3.27.7)
project(Waves)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

include(FetchContent)


add_subdirectory(ui)
add_subdirectory(src)
include_directories(src/)

add_executable(
    waves
    main.cpp
)


target_link_libraries(
    waves
    audio
    UI
)
