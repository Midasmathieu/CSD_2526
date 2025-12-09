cmake_minimum_required(VERSION 3.10)
project(simpleClass)

add_executable(simpleClass)

target_sources(simpleClass PRIVATE
    main.cpp
)
set_property(TARGET simpleClass PROPERTY CXX_STANDARD 20)
