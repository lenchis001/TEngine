file(GLOB_RECURSE tengine_sources_files
    "Sources/*.cpp"
    "Sources/*.c"
)

add_library(TEngine SHARED ${tengine_sources_files})

target_compile_definitions(TEngine PRIVATE TENGINE_EXPORTS)
target_include_directories(TEngine PUBLIC "Sources")

# --------------------- Dependencies ---------------------

# Download and configure GLFW
include(FetchContent)

FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG        master
)

FetchContent_GetProperties(glfw)
if(NOT glfw_POPULATED)
    FetchContent_Populate(glfw)
    add_subdirectory(${glfw_SOURCE_DIR} ${glfw_BINARY_DIR})
endif()

# Set GLFW as an external project
set_target_properties(glfw PROPERTIES FOLDER external)

# Add GLFW includes
target_include_directories(TEngine PRIVATE ${glfw_SOURCE_DIR}/include)

# Add GLFW library
target_link_libraries(TEngine PRIVATE glfw)

# --------------------- Add OpenGL library ---------------------

find_package(OpenGL REQUIRED)
target_link_libraries(TEngine PRIVATE OpenGL::GL)

# --------------------- Add GLEW library ---------------------

# Download and configure GLEW
include(FetchContent)

FetchContent_Declare(
    glew
    GIT_REPOSITORY https://github.com/Perlmint/glew-cmake.git
    GIT_TAG        master
    SOURCE_DIR     ${CMAKE_CURRENT_BINARY_DIR}/glew
)

FetchContent_GetProperties(glew)
if(NOT glew_POPULATED)
    FetchContent_Populate(glew)
    add_subdirectory(${glew_SOURCE_DIR}/build/cmake ${glew_BINARY_DIR})
endif()

# Set GLEW as an external project
set_target_properties(glew PROPERTIES FOLDER external)

# Add GLEW includes
target_include_directories(TEngine PRIVATE ${glew_SOURCE_DIR}/include)

# Add GLEW library
target_link_libraries(TEngine PRIVATE glew)
