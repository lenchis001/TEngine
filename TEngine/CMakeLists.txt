set(TEngine_COMPILE_DEFINITIONS 
    CACHE INTERNAL "${PROJECT_NAME}: Definitions" FORCE)
add_compile_definitions(${TEngine_COMPILE_DEFINITIONS})
include_directories("Sources")

file(GLOB_RECURSE tengine_sources_files
    "Sources/*.cpp"
    "Sources/*.c"
)

add_library(TEngine SHARED ${tengine_sources_files})

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
