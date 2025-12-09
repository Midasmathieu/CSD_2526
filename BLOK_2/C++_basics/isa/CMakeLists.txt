cmake_minimum_required(VERSION 3.10)
project(isaspeaker)

add_executable(isa)

target_sources(isa PRIVATE
    main.cpp
    speaker.cpp
    jbl.cpp
)
set_property(TARGET isa PROPERTY CXX_STANDARD 20)
