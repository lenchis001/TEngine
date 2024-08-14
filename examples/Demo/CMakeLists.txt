# Set the minimum required CMake version
cmake_minimum_required(VERSION 3.12)

file(GLOB_RECURSE demo_sources_files
    "Sources/*.cpp"
    "Sources/*.c"
)

# Add the executable target
add_executable(Demo ${demo_sources_files})

# Include the TEngine library

target_include_directories(Demo PRIVATE "../../TEngine/Sources")

# Link the TEngine library to the executable
target_link_libraries(Demo PRIVATE TEngine)

# Copy Resources directory to the output directory
add_custom_command(TARGET Demo POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/TEngine/BuildinResources"
    "$<TARGET_FILE_DIR:Demo>/BuildinResources"
)

# Copy TEngine library
add_custom_command(TARGET Demo POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    "$<TARGET_FILE_DIR:TEngine>/libTEngine.dll"
    "$<TARGET_FILE_DIR:Demo>/libTEngine.dll"
)