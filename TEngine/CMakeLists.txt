file(GLOB_RECURSE tengine_sources_files
    "Sources/*.cpp"
    "Sources/*.c"
)

add_library(TEngine SHARED ${tengine_sources_files})

target_compile_definitions(TEngine PRIVATE TENGINE_EXPORTS TENGINE_IMAGE_LOADING_IMPORTS)
if(APPLE)
target_compile_definitions(TEngine PRIVATE GL_SILENCE_DEPRECATION)
endif()
target_include_directories(TEngine PUBLIC "Sources")

# Copy Resources directory to the output directory
add_custom_command(TARGET TEngine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/TEngine/BuildinResources"
    "$<TARGET_FILE_DIR:TEngine>/BuildinResources"
)

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
)

FetchContent_GetProperties(glew)
if(NOT glew_POPULATED)
    FetchContent_Populate(glew)

    # Set GLEW to build as a static library
    set(BUILD_SHARED_LIBS OFF CACHE BOOL " " FORCE)
    set(glew-cmake_BUILD_SHARED OFF CACHE BOOL " " FORCE)

    add_subdirectory(${glew_SOURCE_DIR}/build/cmake ${glew_BINARY_DIR})
endif()

# Set GLEW as an external project
set_target_properties(glew PROPERTIES FOLDER external)

# Add GLEW includes
target_include_directories(TEngine PRIVATE ${glew_SOURCE_DIR}/include)

# Add GLEW library
target_link_libraries(TEngine PRIVATE glew_s)

# --------------------- Add OpenAL library ---------------------

# Download and configure OpenAL
include(FetchContent)

set(LIBTYPE STATIC)

FetchContent_Declare(
    openal
    GIT_REPOSITORY https://github.com/kcat/openal-soft.git
    GIT_TAG        1.23.1
)

FetchContent_GetProperties(openal)

if(NOT openal_POPULATED)
    FetchContent_Populate(openal)
    add_subdirectory(${openal_SOURCE_DIR} ${openal_BINARY_DIR})
endif()

# Add OpenAL includes
target_include_directories(TEngine PRIVATE ${openal_SOURCE_DIR}/include)

# Add OpenAL library
target_link_libraries(TEngine PRIVATE OpenAL)

# --------------------- Add ogg library ---------------------

# Download and configure ogg
include(FetchContent)

FetchContent_Declare(
    ogg
    GIT_REPOSITORY https://github.com/xiph/ogg.git
    GIT_TAG        v1.3.5
)

FetchContent_GetProperties(ogg)

if(NOT ogg_POPULATED)
    FetchContent_Populate(ogg)
    add_subdirectory(${ogg_SOURCE_DIR} ${ogg_BINARY_DIR})
endif()

# Add ogg includes
target_include_directories(TEngine PRIVATE ${ogg_SOURCE_DIR}/include)

# Add ogg library
target_link_libraries(TEngine PRIVATE ogg)

# --------------------- Add vorbis library ---------------------

# Download and configure vorbis
include(FetchContent)

FetchContent_Declare(
    vorbis
    GIT_REPOSITORY https://github.com/xiph/vorbis.git
    GIT_TAG        v1.3.6
)

set(OGG_INCLUDE_DIRS ${ogg_SOURCE_DIR}/include)
set(OGG_LIBRARIES ogg)

FetchContent_GetProperties(vorbis)

if(NOT vorbis_POPULATED)
    FetchContent_Populate(vorbis)
    add_subdirectory(${vorbis_SOURCE_DIR} ${vorbis_BINARY_DIR})
endif()

# Add vorbis includes
target_include_directories(TEngine PRIVATE ${vorbis_SOURCE_DIR}/include)

# Add vorbis library
target_link_libraries(TEngine PRIVATE vorbis vorbisfile)

# --------------------- Add boost library ---------------------
target_link_libraries(
  TEngine
  PRIVATE Boost::filesystem)