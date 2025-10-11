cmake_minimum_required(VERSION 3.16)

message(STATUS "RetroFuturaGUI Example CMake Configuration")
#set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
message(STATUS "CMAKE_TOOLCHAIN_FILE: ${CMAKE_TOOLCHAIN_FILE}")


project("RetroFuturaGuiExample" VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(RetroFuturaGUI)

#add_executable(MyExecutable main.cpp)
#target_link_libraries(MyExecutable MyLibrary)