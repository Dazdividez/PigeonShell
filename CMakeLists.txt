#===== System set =====#

cmake_minimum_required(VERSION 3.28)

#===== Project PigeonShell =====#

project(pigeonshell
    VERSION 0.0.1
    DESCRIPTION "Graphic shell for Pigeon Linux"
    LANGUAGES CXX)

#===== find_package =====#

find_package(SFML REQUIRED)

#===== source =====#

add_executable(pigeonshell src/*)

#===== source/subdirectory =====#

add_subdirectory(src/Panels)

#===== target_link_libraries =====#

target_link_libraries(pigeonshell PRIVATE SFML)

#===== CXX_FLAGS =====#
