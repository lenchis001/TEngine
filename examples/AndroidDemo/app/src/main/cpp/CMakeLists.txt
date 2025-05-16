# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

cmake_minimum_required(VERSION 3.22.1)

set(CMAKE_COLOR_MAKEFILE ON)
set(CMAKE_CXX_STANDARD 17)

project("android_demo")

# --------------------- Add TEngine library ---------------------
include(FetchContent)

FetchContent_Declare(
        TEngine
        GIT_REPOSITORY git@github.com:lenchis001/TEngine.git
        GIT_SHALLOW    TRUE
)

FetchContent_GetProperties(tengine)
if(NOT tengine_POPULATED)
    FetchContent_Populate(tengine)

    # Set TEngine to skip building Demo and Editor
    set(BUILD_DEMO OFF CACHE BOOL " " FORCE)
    set(BUILD_ALICE OFF CACHE BOOL " " FORCE)
    set(BUILD_WITH_GLFW OFF CACHE BOOL " " FORCE)
    set(ANDROID ON CACHE BOOL " " FORCE)

    add_subdirectory(${tengine_SOURCE_DIR} ${tengine_BINARY_DIR})
endif()

# -----------------------------------------------------------------------

# Creates your game shared library. The name must be the same as the
# one used for loading in your Kotlin/Java or AndroidManifest.txt files.
add_library(android_demo SHARED
        main.cpp
)

target_include_directories(android_demo PRIVATE ${tengine_SOURCE_DIR}/TEngine/Sources)

# Searches for a package provided by the game activity dependency
find_package(game-activity REQUIRED CONFIG)

# Configure libraries CMake uses to link your target library.
target_link_libraries(android_demo
        # The game activity
        game-activity::game-activity

        # EGL and other dependent libraries required for drawing
        # and interacting with Android system
        EGL
        GLESv3
        jnigraphics
        android
        log
        TEngine
)

# Add post-build command to run a Python script
add_custom_command(TARGET android_demo
                   POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E echo "Running shaders processing..."
                   COMMAND ${PYTHON_EXECUTABLE} ${tengine_SOURCE_DIR}/tools/shader_builder.py "${tengine_SOURCE_DIR}/TEngine/BuildinResources/Shaders" "${CMAKE_SOURCE_DIR}/../assets/BuildinResources/Shaders" "300 es"
                   COMMAND ${CMAKE_COMMAND} -E echo "Shaders processing completed."
                   COMMENT "Executing post-build shaders processing")

# Copy the generated .so library to the Assets directory
add_custom_command(TARGET android_demo POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        "$<TARGET_FILE:ObjLoadingPlugin>"
        "${CMAKE_SOURCE_DIR}/../assets/Plugins/MeshLoading/ObjLoadingPlugin.so"
)

add_custom_command(TARGET android_demo POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        "$<TARGET_FILE:GltfLoadingPlugin>"
        "${CMAKE_SOURCE_DIR}/../assets/Plugins/MeshLoading/GltfLoadingPlugin.so"
)

# Copy the generated .so library to the Assets directory
add_custom_command(TARGET android_demo POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        "$<TARGET_FILE:BmpLoadingPlugin>"
        "${CMAKE_SOURCE_DIR}/../assets/Plugins/ImageLoading/BmpLoadingPlugin.so"
)

# Copy the generated .so library to the Assets directory
add_custom_command(TARGET android_demo POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        "$<TARGET_FILE:PngLoadingPlugin>"
        "${CMAKE_SOURCE_DIR}/../assets/Plugins/ImageLoading/PngLoadingPlugin.so"
)