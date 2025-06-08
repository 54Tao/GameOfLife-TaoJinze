cmake_minimum_required(VERSION 3.16)
project(GameOfLife)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 COMPONENTS Core Widgets REQUIRED)

add_executable(GameOfLife
    main.cpp
    LifeWidget.h
    LifeWidget.cpp
)

target_link_libraries(GameOfLife PRIVATE
    Qt6::Core
    Qt6::Widgets
)
