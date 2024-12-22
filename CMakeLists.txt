cmake_minimum_required(VERSION 3.1)
project(GameEngine CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Adding Raylib
include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # don't build the supplied example games

FetchContent_Declare(
    raylib
    GIT_REPOSITORY "https://github.com/raysan5/raylib.git"
    GIT_TAG "master"
    GIT_PROGRESS TRUE
)

FetchContent_MakeAvailable(raylib)

# Adding our source files
file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/sources/*.cpp")
set(PROJECT_INCLUDE "${CMAKE_CURRENT_LIST_DIR}/sources/") # Define PROJECT_INCLUDE to be the path to the include directory of the project

# Declaring our executable
add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCES}  "sources/GameObject.h" "sources/GameObject.cpp"   "sources/Components/RectangleRenderer.h" "sources/Components/RectangleRenderer.cpp" "sources/Components/RectangleCollider.h" "sources/Components/RectangleCollider.cpp" "sources/Components/PlayerController.h" "sources/Components/PlayerController.cpp" "sources/Components/CollisionColorChanger.h" "sources/Components/CollisionColorChanger.cpp" "sources/GameManager.cpp" "sources/GameManager.h" "sources/Components/MyTransform.cpp" "sources/Components/MyTransform.h" "sources/ComponentPool.h"  "sources/Components/MyComponent.h"  "sources/Components/MyComponent.cpp"       "sources/StackAllocator.h" "sources/StackAllocator.cpp" "sources/Components/Pathfinder.h" "sources/Components/Pathfinder.cpp"  "sources/AStar/AStarNode.h" "sources/AStar/AStar.h" "sources/AStar/AStar.cpp" "sources/AStar/Grid.h" "sources/AStar/Grid.cpp")
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_INCLUDE})
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

# Setting ASSETS_PATH
target_compile_definitions(${PROJECT_NAME} PUBLIC ASSETS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/assets/") # Set the asset path macro to the absolute path on the dev machine
#target_compile_definitions(${PROJECT_NAME} PUBLIC ASSETS_PATH="./assets") # Set the asset path macro in release mode to a relative path that assumes the assets folder is in the same directory as the game executable