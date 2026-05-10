cmake_minimum_required(VERSION 3.8)

project(Splendor)

include(FetchContent)

set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG master
)

FetchContent_MakeAvailable(raylib)

add_executable(Splendor
    source/main.cpp
 "include/Card.h" "include/Player.h" "include/Game.h" "source/utils.cpp" "include/utils.h" "source/Game.cpp")


target_include_directories(Splendor PRIVATE include)

target_link_libraries(Splendor raylib)

# Setting ASSETS_PATH (its just a macro that will be replaced with the actual path during compilation)
# to the absolute path of the assets folder on the development machine. This allows the game to find its assets correctly when running from the build directory.)
# ASSETS_PATH "test.png" becomes "/path/to/your/assets/test.png"
target_compile_definitions(${PROJECT_NAME} PUBLIC ASSETS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/assets/") 

if (CMAKE_VERSION VERSION_GREATER 3.12)
    set_property(TARGET Splendor PROPERTY CXX_STANDARD 20)
endif()