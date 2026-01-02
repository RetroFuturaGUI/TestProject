cmake_minimum_required(VERSION 3.16..)

message(STATUS "RetroFuturaGUI TestProject CMake Configuration")
#set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
message(STATUS "CMAKE_TOOLCHAIN_FILE: ${CMAKE_TOOLCHAIN_FILE}")


project("TestProject" VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/RetroFuturaGUI")

# Check if DYNLIB_MODE is set
if(DYNLIB_MODE)
    message(STATUS "Building as a shared library (DLL)")
    add_library(TestProject SHARED
        "${CMAKE_CURRENT_SOURCE_DIR}/source/generated/main.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/source/generated/impl/MainWindow_setup.cpp"
    )
    set_target_properties(TestProject PROPERTIES OUTPUT_NAME "TestProjectNative")
else()
    message(STATUS "Building as an executable")
    add_executable(TestProject
        "${CMAKE_CURRENT_SOURCE_DIR}/source/generated/main.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/source/generated/impl/MainWindow_setup.cpp"
    )
endif()

target_include_directories("TestProject" PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/source"
    "${CMAKE_CURRENT_SOURCE_DIR}/source/code"
    "${CMAKE_CURRENT_SOURCE_DIR}/source/generated"
    "${CMAKE_CURRENT_SOURCE_DIR}/source/generated/impl"
)

target_link_libraries("TestProject" PRIVATE
    "RetroFuturaGUI"
)

add_custom_command(TARGET "TestProject" POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/RetroFuturaGUI/source/Shaders/ShaderSource"
        "$<TARGET_FILE_DIR:TestProject>/ShaderSource"
)

add_custom_command(TARGET "TestProject" POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/RetroFuturaGUI/Resources"
        "$<TARGET_FILE_DIR:TestProject>/Resources"
)

if(DYNLIB_MODE)
    add_custom_command(TARGET TestProject POST_BUILD
        COMMAND dotnet build "${CMAKE_CURRENT_SOURCE_DIR}/source/code/CSharpProject/TestProject.csproj" --configuration Debug
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/source/code/CSharpProject"
        COMMENT "Building C# project after DLL..."
    )
endif()


#exe mode:
#run cmake (DEBUG):   & "C:\Program Files\CMake\bin\cmake.exe" .. CMakeLists.txt -DTARGETPLATFORM=x64-windows -DCMAKE_TOOLCHAIN_FILE="$env:VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake" -DBUILDTYPE=Debug   -B x64-windows
#run cmake (RELEASE): & "C:\Program Files\CMake\bin\cmake.exe" .. CMakeLists.txt -DTARGETPLATFORM=x64-windows -DCMAKE_TOOLCHAIN_FILE="$env:VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake" -DBUILDTYPE=Release -B x64-windows
#build: & "C:\Program Files\CMake\bin\cmake.exe" --build x64-windows
#run: x64-windows/Debug/TestProject.exe

#dll mode
#run cmake (DEBUG):   & "C:\Program Files\CMake\bin\cmake.exe" .. CMakeLists.txt -DTARGETPLATFORM=x64-windows -DCMAKE_TOOLCHAIN_FILE="$env:VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake" -DBUILDTYPE=Debug   -DDYNLIN=true -B x64-windows
#run cmake (RELEASE): & "C:\Program Files\CMake\bin\cmake.exe" .. CMakeLists.txt -DTARGETPLATFORM=x64-windows -DCMAKE_TOOLCHAIN_FILE="$env:VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake" -DBUILDTYPE=Release -DDYNLIN=true -B x64-windows
#build: & "C:\Program Files\CMake\bin\cmake.exe" --build x64-windows