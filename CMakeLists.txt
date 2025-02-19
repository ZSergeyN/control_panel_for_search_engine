cmake_minimum_required (VERSION 3.16)

project (ControlPanel VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)

find_package(Qt6 COMPONENTS Widgets Core Gui REQUIRED)

add_executable(ControlPanel main.cpp controlPanel.h controlPanel.ui
    controlPanel.cpp)

target_link_libraries(ControlPanel Qt6::Widgets Qt6::Core Qt6::Gui)
