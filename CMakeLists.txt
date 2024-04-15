cmake_minimum_required(VERSION 3.24)
project(SongPlayer VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

find_package(Qt6 REQUIRED COMPONENTS Core Quick)

qt_standard_project_setup(REQUIRES 6.7)

add_subdirectory(SourceFiles)
