FetchContent_Declare(
    PortAudio
    GIT_REPOSITORY https://github.com/PortAudio/portaudio.git
    GIT_TAG 5a1920d
  )
FetchContent_MakeAvailable(PortAudio)


add_library(
    audio
    WaveGenerator.cpp
    WavFile.cpp
    AudioStream.cpp
    WavSource.cpp
    SourcePlayer.cpp
    SignalSource.cpp
)


target_link_libraries(
    audio
    PortAudio
)