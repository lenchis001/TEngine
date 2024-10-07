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

# Include the TEngine library
target_include_directories(Alice PRIVATE "../../TEngine/Sources")

# Link the TEngine library to the executable
target_link_libraries(Alice PRIVATE TEngine)

# Copy alice resources directory to the output directory
add_custom_command(TARGET Alice POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/Editor/Alice/Resources"
    "$<TARGET_FILE_DIR:Alice>/AliceResources"
)

# Copy TEngine library
add_custom_command(TARGET Alice POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    "$<TARGET_FILE_DIR:TEngine>/${CMAKE_SHARED_LIBRARY_PREFIX}TEngine${CMAKE_SHARED_LIBRARY_SUFFIX}"
    "$<TARGET_FILE_DIR:Alice>/"
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

if(NOT wxwidgets_POPULATED)
    FetchContent_Populate(wxwidgets)
    add_subdirectory(${wxwidgets_SOURCE_DIR} ${wxwidgets_BINARY_DIR})
endif()

target_link_libraries(Alice PRIVATE wx::net wx::core wx::base)