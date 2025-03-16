# Set the minimum required CMake version
cmake_minimum_required(VERSION 3.10)

project(SlotMachine)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set vcpkg toolchain file (adjust the path as needed)
if (WIN32)
    set(CMAKE_TOOLCHAIN_FILE "C:vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
elseif (UNIX)
    set(CMAKE_TOOLCHAIN_FILE "$ENV{HOME}/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
endif()

# Find SFML
find_package(SFML REQUIRED COMPONENTS graphics window system audio)

# Source files
set(SOURCE
    main.cpp
    Reel.cpp
    States.cpp
    StateMachine.cpp
    UserInterface.cpp
    SlotMachine.cpp
)

# Create the executable
add_executable(SlotMachine ${SOURCE})

# Link SFML libraries
target_link_libraries(SlotMachine PRIVATE sfml-graphics sfml-window sfml-system sfml-audio)