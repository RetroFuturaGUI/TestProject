cmake_minimum_required(VERSION 3.16..)

message(STATUS "-- RetroFuturaGUI TestProject CMake Configuration")
#set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
message(STATUS "CMAKE_TOOLCHAIN_FILE: ${CMAKE_TOOLCHAIN_FILE}")

project("TestProject" VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(DEFINED LANG AND LANG)
    message(STATUS "-- Target Lang: ${LANG}")
    message(STATUS "-- Building a library")
    add_library(TestProject SHARED
        "${CMAKE_CURRENT_SOURCE_DIR}/source/generated/main.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/source/generated/impl/MainWindow_setup.cpp"
    )
    set_target_properties(TestProject PROPERTIES OUTPUT_NAME "TestProjectNative")
    set(DYNLIB_MODE ON CACHE BOOL "Build as a dynamic library")
    add_definitions(-DDYNLIB_MODE) #needs to be globally available
else()
    message(STATUS "-- Target Lang: C++")
    message(STATUS "-- Building as an executable")
    add_executable("TestProject"
        "${CMAKE_CURRENT_SOURCE_DIR}/source/generated/main.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/source/generated/impl/MainWindow_setup.cpp"
    )
endif()


if(MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -Werror -Wreturn-type -Wunused-includes)
endif()

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/RetroFuturaGUI")

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

if(LANG MATCHES "CSharp")
    add_custom_command(TARGET TestProject POST_BUILD
        COMMAND dotnet build "${CMAKE_CURRENT_SOURCE_DIR}/source/code/CSharpProject/TestProject.csproj" --configuration Debug
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/source/code/CSharpProject"
        COMMENT "Building C# project after DLL..."
    )

    add_custom_command(TARGET TestProject POST_BUILD
        COMMAND ${CMAKE_COMMAND}
                -DSOURCE_DIR="${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}"
                -DDEST_DIR="${CMAKE_CURRENT_SOURCE_DIR}/source/code/CSharpProject/bin/${CMAKE_BUILD_TYPE}/net8.0"
                -P "${CMAKE_CURRENT_SOURCE_DIR}/copy_script.cmake"
        COMMENT "Copying build output (including subfolders) to C# directory..."
    )
elseif(LANG MATCHES "Python")
    add_custom_command(TARGET TestProject POST_BUILD
        COMMAND ${CMAKE_COMMAND}
                -DSOURCE_DIR="${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}"
                -DDEST_DIR="${CMAKE_CURRENT_SOURCE_DIR}/source/code/Python"
                -P "${CMAKE_CURRENT_SOURCE_DIR}/copy_script.cmake"
        COMMENT "Copying build output (including subfolders) to Python directory..."
    )
endif()


#exe mode:
#run cmake (DEBUG):   & "C:\Program Files\CMake\bin\cmake.exe" .. CMakeLists.txt -DTARGETPLATFORM=x64-windows -DCMAKE_TOOLCHAIN_FILE="$env:VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake" -DCMAKE_BUILD_TYPE=Debug   -B x64-windows
#run cmake (RELEASE): & "C:\Program Files\CMake\bin\cmake.exe" .. CMakeLists.txt -DTARGETPLATFORM=x64-windows -DCMAKE_TOOLCHAIN_FILE="$env:VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake" -DCMAKE_BUILD_TYPE=Release -B x64-windows
#build: & "C:\Program Files\CMake\bin\cmake.exe" --build x64-windows
#run: x64-windows/Debug/TestProject.exe

#dll mode
#run cmake (DEBUG):   & "C:\Program Files\CMake\bin\cmake.exe" .. CMakeLists.txt -DTARGETPLATFORM=x64-windows -DCMAKE_TOOLCHAIN_FILE="$env:VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake" -DCMAKE_BUILD_TYPE=Debug   -DLANG=<LANG> -B x64-windows
#run cmake (RELEASE): & "C:\Program Files\CMake\bin\cmake.exe" .. CMakeLists.txt -DTARGETPLATFORM=x64-windows -DCMAKE_TOOLCHAIN_FILE="$env:VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake" -DCMAKE_BUILD_TYPE=Release -DLANG=<LANG> -B x64-windows
#build: & "C:\Program Files\CMake\bin\cmake.exe" --build x64-windows

#replace <LANG> with CSharp or Python