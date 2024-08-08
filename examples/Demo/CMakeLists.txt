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