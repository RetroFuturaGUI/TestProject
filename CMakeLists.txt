cmake_minimum_required(VERSION 3.16)

message(STATUS "RetroFuturaGUI TestProject CMake Configuration")
#set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
message(STATUS "CMAKE_TOOLCHAIN_FILE: ${CMAKE_TOOLCHAIN_FILE}")


project("TestProject" VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/RetroFuturaGUI")

add_executable("TestProject" 
    "${CMAKE_CURRENT_SOURCE_DIR}/source/generated/main.cpp"
)

target_include_directories("TestProject"  PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/source"
    "${CMAKE_CURRENT_SOURCE_DIR}/source/code"
    "${CMAKE_CURRENT_SOURCE_DIR}/source/generated"
)

target_link_libraries("TestProject" PRIVATE
    "RetroFuturaGUI"
)

#run cmake:  & "C:\Program Files\CMake\bin\cmake.exe" .. CMakeLists.txt -DTARGETPLATFORM=x64-windows -DCMAKE_TOOLCHAIN_FILE="$env:VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake" -B x64-windows
#build: & "C:\Program Files\CMake\bin\cmake.exe" --build x64-windows
#run: x64-windows/Debug/TestProject.exe