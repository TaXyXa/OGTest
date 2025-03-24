# Set the minimum required CMake version
cmake_minimum_required(VERSION 3.10)

project(SlotMachine)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#SFML
set(SFML_DIR "${CMAKE_SOURCE_DIR}/SFML-2.6.0/lib/cmake/SFML")
find_package(SFML 2.6.0 COMPONENTS graphics window system REQUIRED)

# Source files
set(SOURCE
    Source/main.cpp
    Source/Reel.cpp
    Source/States.cpp
    Source/StateMachine.cpp
    Source/UserInterface.cpp
)

# Create the executable
add_executable(SlotMachine  ${SOURCE})

# Link SFML libraries
target_link_libraries(SlotMachine PRIVATE sfml-graphics sfml-window sfml-system)
