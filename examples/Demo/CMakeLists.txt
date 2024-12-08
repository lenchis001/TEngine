# Set the minimum required CMake version
cmake_minimum_required(VERSION 3.12)

file(GLOB_RECURSE demo_sources_files
    "Sources/*.cpp"
    "Sources/*.c"
)

# Add the executable target
# if (WIN32)
#     add_executable(Demo WIN32 ${demo_sources_files})
# else()
    add_executable(Demo ${demo_sources_files})
#endif()

# Include the TEngine library

target_include_directories(Demo PRIVATE "../../TEngine/Sources")

# Link the TEngine library to the executable
target_link_libraries(Demo PRIVATE TEngine)

# Find Python interpreter
find_package(PythonInterp 3 REQUIRED)

# Add post-build command to run a Python script
add_custom_command(TARGET Demo
                   POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E echo "Running shaders processing..."
                   COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_SOURCE_DIR}/tools/shader_builder.py "${CMAKE_SOURCE_DIR}/TEngine/BuildinResources/Shaders" "$<TARGET_FILE_DIR:Demo>/BuildinResources/Shaders"
                   COMMAND ${CMAKE_COMMAND} -E echo "Shaders processing completed."
                   COMMENT "Executing post-build shaders processing")

# Copy demo resources directory to the output directory
add_custom_command(TARGET Demo POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/examples/Demo/DemoResources"
    "$<TARGET_FILE_DIR:Demo>/DemoResources"
)

# Copy TEngine library to demo
add_custom_command(TARGET Demo POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    "$<TARGET_FILE:TEngine>"
    "$<TARGET_FILE_DIR:Demo>/"
)

# Copy plugin library to Demo output directory
add_custom_command(TARGET Demo POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    "$<TARGET_FILE:BmpLoadingPlugin>"
    "$<TARGET_FILE_DIR:Demo>/Plugins/ImageLoading/${CMAKE_SHARED_LIBRARY_PREFIX}BmpLoadingPlugin${CMAKE_SHARED_LIBRARY_SUFFIX}"
)
add_custom_command(TARGET Demo POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    "$<TARGET_FILE:PngLoadingPlugin>"
    "$<TARGET_FILE_DIR:Demo>/Plugins/ImageLoading/${CMAKE_SHARED_LIBRARY_PREFIX}PngLoadingPlugin${CMAKE_SHARED_LIBRARY_SUFFIX}"
)


# Copy plugin library to example output directory
add_custom_command(TARGET Demo POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    "$<TARGET_FILE:ObjLoadingPlugin>"
    "$<TARGET_FILE_DIR:Demo>/Plugins/MeshLoading/${CMAKE_SHARED_LIBRARY_PREFIX}ObjLoadingPlugin${CMAKE_SHARED_LIBRARY_SUFFIX}"
)