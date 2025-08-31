#===== System set =====#

cmake_minimum_required(VERSION 3.28)

#===== include =====#

#===== Project PigeonShell/Panels =====#

project(pigeonshell_panels
    VERSION 0.0.1
    DESCRIPTION "User Control Panels for PigeonShell"
    LANGUAGES CXX)

#===== fetch_content ======#

#===== find_package =====#

find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)

#===== source =====#
add_executable(dock src/dock/dock.cpp src/dock/dockbar.cpp)
add_executable(taskbar src/task/taskbar.cpp)

#===== source/subdirectory =====#

#add_subdirectory(src/)

#===== target_link_libraries =====#

target_link_libraries(dock PRIVATE sfml-graphics sfml-window sfml-system)

#===== set =====#

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Panels/build)
