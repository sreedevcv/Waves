cmake_minimum_required(VERSION 3.27.7)
project(Waves)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
set(CMAKE_CXX_)

include(FetchContent)

FetchContent_Declare(
    PortAudio
    GIT_REPOSITORY https://github.com/PortAudio/portaudio.git
    GIT_TAG 5a1920d
  )
FetchContent_MakeAvailable(PortAudio)

add_executable(
    waves
    src/main.cpp
    src/WaveGenerator.cpp
    src/WavFile.cpp
    src/AudioStream.cpp
)


target_link_libraries(
    waves
    PortAudio
)
