# Set the minimum required CMake version
cmake_minimum_required(VERSION 3.12)

file(GLOB_RECURSE alice_sources_files
    "Sources/*.cpp"
    "Sources/*.c"
)

# Add the executable target
if (WIN32)
    add_executable(Alice WIN32 ${alice_sources_files})
else()
    add_executable(Alice ${alice_sources_files})
endif()

target_include_directories(Alice PUBLIC "Sources")

# Include the TEngine library
target_include_directories(Alice PRIVATE "../../TEngine/Sources")

# Link the TEngine library to the executable
target_link_libraries(Alice PRIVATE TEngine)

# Add custom command to compile the manifest file into a resource file
if (MINGW)
    execute_process(
        COMMAND ${CMAKE_RC_COMPILER} -i ${CMAKE_SOURCE_DIR}/Editor/Alice/Sources/resources.rc -o ${CMAKE_BINARY_DIR}/resources.o)

    # Link the resource file with the executable
    target_sources(Alice PRIVATE ${CMAKE_BINARY_DIR}/resources.o)
endif()

# Copy alice resources directory to the output directory
add_custom_command(TARGET Alice POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/Editor/Alice/Resources"
    "$<TARGET_FILE_DIR:Alice>/AliceResources"
)

# Copy TEngine library to Alice
add_custom_command(TARGET Alice POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    "$<TARGET_FILE:TEngine>"
    "$<TARGET_FILE_DIR:Alice>/"
)

# Add post-build command to run a Python script
add_custom_command(TARGET Alice
                   POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E echo "Running shaders processing..."
                   COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_SOURCE_DIR}/tools/shader_builder.py "${CMAKE_SOURCE_DIR}/TEngine/BuildinResources/Shaders" "$<TARGET_FILE_DIR:Alice>/BuildinResources/Shaders" "#version 330 core"
                   COMMAND ${CMAKE_COMMAND} -E echo "Shaders processing completed."
                   COMMENT "Executing post-build shaders processing")

# Copy plugin library to Alice output directory
add_custom_command(TARGET Alice POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    "$<TARGET_FILE:BmpLoadingPlugin>"
    "$<TARGET_FILE_DIR:Alice>/Plugins/ImageLoading/${CMAKE_SHARED_LIBRARY_PREFIX}BmpLoadingPlugin${CMAKE_SHARED_LIBRARY_SUFFIX}"
)

# Copy plugin library to Alice output directory
add_custom_command(TARGET Alice POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    "$<TARGET_FILE:ObjLoadingPlugin>"
    "$<TARGET_FILE_DIR:Alice>/Plugins/MeshLoading/${CMAKE_SHARED_LIBRARY_PREFIX}ObjLoadingPlugin${CMAKE_SHARED_LIBRARY_SUFFIX}"
)

# --------------------- Dependencies ---------------------

# Download and configure wxWidgets

include(FetchContent)

FetchContent_Declare(
    wxwidgets
    GIT_REPOSITORY https://github.com/wxWidgets/wxWidgets.git
    GIT_TAG        v3.2.6
    GIT_SHALLOW    TRUE
)

FetchContent_GetProperties(wxwidgets)

unset (wxUSE_STL CACHE)
set(wxUSE_STL ON CACHE BOOL " " FORCE)

if(NOT wxwidgets_POPULATED)
    FetchContent_Populate(wxwidgets)
    add_subdirectory(${wxwidgets_SOURCE_DIR} ${wxwidgets_BINARY_DIR})
endif()

target_link_libraries(Alice PRIVATE wx::net wx::core wx::base)