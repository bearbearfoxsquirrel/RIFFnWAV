cmake_minimum_required(VERSION 3.6)
project(Speech_n_Wavs)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    main.cpp
    RIFF.cpp
    RIFF.h
    WAV.cpp
    WAV.h SoundEditor.h SoundEditor.cpp SoundIO.h SoundIO.cpp)

add_executable(Speech_n_Wavs ${SOURCE_FILES})