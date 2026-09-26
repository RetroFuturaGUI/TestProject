cmake_minimum_required(VERSION 3.16..)

message(STATUS "-- RetroFuturaGUI TestProject CMake Configuration")
#set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
message(STATUS "CMAKE_TOOLCHAIN_FILE: ${CMAKE_TOOLCHAIN_FILE}")

project("TestProject" VERSION 0.1.0)

if(NOT DEFINED TARGETPLATFORM)
    if(WIN32)
        set(TARGETPLATFORM "x64-Windows" CACHE STRING "Target platform for the build")
    else()
        set(TARGETPLATFORM "x64-Linux" CACHE STRING "Target platform for the build")
    endif()
endif()

message(STATUS "-- Target Platform: ${TARGETPLATFORM}")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)

if(DEFINED LANG AND LANG)
    message(STATUS "-- Target Lang: ${LANG}")
    message(STATUS "-- Building a library")
    add_library(TestProject SHARED
        "${CMAKE_CURRENT_SOURCE_DIR}/source/generated/main.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/source/generated/impl/Windows/MainWindow_setup.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/source/generated/impl/Scenes/MainScene_setup.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/source/generated/impl/Scenes/MenuBarScene_setup.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/source/code/MainScene.cpp"
    )
    set_target_properties(TestProject PROPERTIES OUTPUT_NAME "TestProjectNative")
    set(DYNLIB_MODE ON CACHE BOOL "Build as a dynamic library")
    add_definitions(-DDYNLIB_MODE) #needs to be globally available
else()
    message(STATUS "-- Target Lang: C++")
    message(STATUS "-- Building as an executable")
    add_executable("TestProject"
        "${CMAKE_CURRENT_SOURCE_DIR}/source/generated/main.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/source/generated/impl/Windows/MainWindow_setup.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/source/generated/impl/Scenes/MainScene_setup.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/source/generated/impl/Scenes/MenuBarScene_setup.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/source/code/MainScene.cpp"
    )
endif()

string(TOLOWER "${TARGETPLATFORM}" TARGETPLATFORM_LOWER)

if(TARGETPLATFORM_LOWER STREQUAL "x64-linux")
    target_compile_definitions(TestProject PRIVATE TARGET_PLATFORM_LINUX)
elseif(TARGETPLATFORM_LOWER STREQUAL "x64-windows")
    target_compile_definitions(TestProject PRIVATE
        TARGET_PLATFORM_WINDOWS
        WIN32 _WIN32 _WIN64
        UNICODE _UNICODE
        $<$<CONFIG:Debug>:_DEBUG>
        $<$<CONFIG:Release>:NDEBUG>
    )
else()
    message(WARNING "Unknown TARGETPLATFORM '${TARGETPLATFORM}'. clangd will not get platform-specific defines.")
endif()

if(MSVC)
    add_compile_options(/W4 /WX)
else()
    # GCC doesn't support -Wunused-includes; only enable when using Clang
    if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        add_compile_options(-Wall -Wextra -Werror -Wreturn-type -Wunused-includes)
    else()
        add_compile_options(-Wall -Wextra -Werror -Wreturn-type)
    endif()
endif()

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/RetroFuturaGUI")

target_include_directories("TestProject" PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/source"
    "${CMAKE_CURRENT_SOURCE_DIR}/source/code"
    "${CMAKE_CURRENT_SOURCE_DIR}/source/generated"
    "${CMAKE_CURRENT_SOURCE_DIR}/source/generated/impl"
    "${CMAKE_CURRENT_SOURCE_DIR}/source/generated/impl/Windows"
    "${CMAKE_CURRENT_SOURCE_DIR}/source/generated/impl/Scenes"
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
    add_custom_command(TARGET TestProject
        COMMAND ${CMAKE_COMMAND} -E copy
        "${CMAKE_CURRENT_SOURCE_DIR}/RetroFuturaGUI/Resources/Bindings/RetroFuturaGuiBinding.cs"
        "${CMAKE_CURRENT_SOURCE_DIR}/source/code/CSharpProject/RetroFuturaGuiBinding.cs"
        COMMENT "Copying binding file"
    )

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
elseif(
LANG MATCHES "Rust")
        add_custom_command(TARGET TestProject
        COMMAND ${CMAKE_COMMAND} -E copy
        "${CMAKE_CURRENT_SOURCE_DIR}/RetroFuturaGUI/Resources/Bindings/RetroFuturaGuiBinding.rs"
        "${CMAKE_CURRENT_SOURCE_DIR}/source/code/RustProject/RetroFuturaGuiBinding.rs"
        COMMENT "Copying binding file"
    )

    add_custom_command(TARGET TestProject POST_BUILD
        COMMAND cargo build --manifest-path "${CMAKE_CURRENT_SOURCE_DIR}/source/code/RustProject/Cargo.toml" --debug
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/source/code/RustProject"
        COMMENT "Building Rust project after DLL..."
)
elseif(LANG MATCHES "Python")
    add_custom_command(TARGET TestProject POST_BUILD
        COMMAND ${CMAKE_COMMAND}
                -DSOURCE_DIR="${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}"
                -DDEST_DIR="${CMAKE_CURRENT_SOURCE_DIR}/source/code/Python"
                -P "${CMAKE_CURRENT_SOURCE_DIR}/copy_script.cmake"
        COMMENT "Copying build output (including subfolders) to Python directory..."

        COMMAND ${CMAKE_COMMAND} -E copy
        "${CMAKE_CURRENT_SOURCE_DIR}/RetroFuturaGUI/Resources/Bindings/RetroFuturaGuiBinding.py"
        "${CMAKE_CURRENT_SOURCE_DIR}/source/code/Python/RetroFuturaGuiBinding.py"
    )
endif()


#exe mode Windows:
#run cmake (DEBUG):   & "C:\Program Files\CMake\bin\cmake.exe" -S .. -G Ninja -DTARGETPLATFORM=x64-windows -DCMAKE_TOOLCHAIN_FILE="$env:VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake" -DCMAKE_BUILD_TYPE=Debug   -B x64-windows
#run cmake (RELEASE): & "C:\Program Files\CMake\bin\cmake.exe" -S .. -G Ninja -DTARGETPLATFORM=x64-windows -DCMAKE_TOOLCHAIN_FILE="$env:VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake" -DCMAKE_BUILD_TYPE=Release -B x64-windows
#build: & "C:\Program Files\CMake\bin\cmake.exe" --build x64-windows
#run: x64-windows/Debug/TestProject.exe

#exe mode Linux:
#run cmake (DEBUG):   cmake -S .. -G Ninja -DTARGETPLATFORM=x64-Linux -DCMAKE_TOOLCHAIN_FILE="$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake" -DCMAKE_BUILD_TYPE=Debug   -B x64-Linux
#run cmake (RELEASE): cmake -S .. -G Ninja -DTARGETPLATFORM=x64-Linux -DCMAKE_TOOLCHAIN_FILE="$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake" -DCMAKE_BUILD_TYPE=Release -B x64-Linux
#build: cmake --build x64-Linux
#run: ./x64-Linux/TestProject

#dll mode Windows:
#run cmake (DEBUG):   & "C:\Program Files\CMake\bin\cmake.exe" -S .. -G Ninja -DTARGETPLATFORM=x64-windows -DCMAKE_TOOLCHAIN_FILE="$env:VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake" -DCMAKE_BUILD_TYPE=Debug   -DLANG=<LANG> -B x64-windows
#run cmake (RELEASE): & "C:\Program Files\CMake\bin\cmake.exe" -S .. -G Ninja -DTARGETPLATFORM=x64-windows -DCMAKE_TOOLCHAIN_FILE="$env:VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake" -DCMAKE_BUILD_TYPE=Release -DLANG=<LANG> -B x64-windows
#build: & "C:\Program Files\CMake\bin\cmake.exe" --build x64-windows

#replace <LANG> with CSharp, Python or Rust