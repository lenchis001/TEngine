file(GLOB_RECURSE tengine_sources_files
    "Sources/*.cpp"
    "Sources/*.c"
    "Sources/*.mm"
)

add_library(TEngine SHARED ${tengine_sources_files})

target_compile_definitions(TEngine PRIVATE TENGINE_EXPORTS TENGINE_IMAGE_LOADING_IMPORTS)
if(APPLE)
target_compile_definitions(TEngine PRIVATE GL_SILENCE_DEPRECATION)
endif()
if(DEBUG)
    target_compile_definitions(TEngine PRIVATE TENGINE_DEBUG)
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
    GIT_TAG        3.4
    GIT_SHALLOW    TRUE
)

FetchContent_GetProperties(glfw)
if(NOT glfw_POPULATED)
    FetchContent_Populate(glfw)

    set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

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
    GIT_TAG        glew-cmake-2.2.0
    GIT_SHALLOW    TRUE
)

FetchContent_GetProperties(glew)
if(NOT glew_POPULATED)
    FetchContent_Populate(glew)

    # Set GLEW to build as a static library
    set(BUILD_SHARED_LIBS OFF CACHE BOOL " " FORCE)
    set(glew-cmake_BUILD_SHARED OFF CACHE BOOL " " FORCE)
    set(ONLY_LIBS ON CACHE BOOL " " FORCE)

    add_subdirectory(${glew_SOURCE_DIR} ${glew_BINARY_DIR})
endif()

# Add GLEW includes
target_include_directories(TEngine PRIVATE ${glew_SOURCE_DIR}/include)

# Add GLEW library
target_link_libraries(TEngine PRIVATE libglew_static)

# --------------------- Add OpenAL library ---------------------

# Download and configure OpenAL
include(FetchContent)

set(LIBTYPE STATIC)

FetchContent_Declare(
    openal
    GIT_REPOSITORY https://github.com/kcat/openal-soft.git
    GIT_TAG        1.23.1
    GIT_SHALLOW    TRUE
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
    GIT_SHALLOW    TRUE
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
    GIT_SHALLOW    TRUE
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
  PRIVATE Boost::filesystem Boost::json)

  # --------------------- Add ImGui library ---------------------

# Download and configure ImGui
include(FetchContent)

FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG        v1.91.2
    GIT_SHALLOW    TRUE
)

FetchContent_GetProperties(imgui)

if(NOT imgui_POPULATED)
    FetchContent_Populate(imgui)
endif()

target_include_directories(TEngine PRIVATE ${imgui_SOURCE_DIR} ${imgui_SOURCE_DIR}/backends)
target_sources(TEngine PRIVATE 
    ${imgui_SOURCE_DIR}/imgui.cpp
    ${imgui_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_SOURCE_DIR}/imgui_widgets.cpp
    ${imgui_SOURCE_DIR}/imgui_tables.cpp
    ${imgui_SOURCE_DIR}/imgui_demo.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp)

# --------------------- Add bullet physics library ---------------------

# Download and configure bullet
include(FetchContent)

FetchContent_Declare(
    bullet
    URL https://codeload.github.com/bulletphysics/bullet3/tar.gz/refs/tags/3.25
)

FetchContent_GetProperties(bullet)

unset(BUILD_BULLET2_DEMOS CACHE)
set(BUILD_BULLET2_DEMOS OFF CACHE BOOL " " FORCE)
unset(BUILD_CPU_DEMOS CACHE)
set(BUILD_CPU_DEMOS OFF CACHE BOOL " " FORCE)
unset(BUILD_OPENGL3_DEMOS CACHE)
set(BUILD_OPENGL3_DEMOS OFF CACHE BOOL " " FORCE)
unset (BUILD_UNIT_TESTS CACHE)
set(BUILD_UNIT_TESTS OFF CACHE BOOL " " FORCE)

if(NOT bullet_POPULATED)
    FetchContent_Populate(bullet)
    add_subdirectory(${bullet_SOURCE_DIR} ${bullet_BINARY_DIR})
endif()

# Add bullet includes
target_include_directories(TEngine PRIVATE ${bullet_SOURCE_DIR}/src)

# Add bullet library
target_link_libraries(TEngine PRIVATE BulletDynamics BulletCollision LinearMath)

# --------------------- Add CURL library -------------------------------
include(FetchContent)

FetchContent_Declare(
    curl
    GIT_REPOSITORY https://github.com/curl/curl.git
    GIT_TAG        curl-8_11_0
    GIT_SHALLOW    TRUE
)

FetchContent_GetProperties(curl)

set(BUILD_CURL_EXE OFF CACHE BOOL " " FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL " " FORCE)
set(BUILD_STATIC_LIBS ON CACHE BOOL " " FORCE)
set(CURL_DISABLE_INSTALL ON CACHE BOOL " " FORCE)

if(NOT curl_POPULATED)
    FetchContent_Populate(curl)
    add_subdirectory(${curl_SOURCE_DIR} ${curl_BINARY_DIR})
endif()

# Add ogg includes
target_include_directories(TEngine PRIVATE ${curl_SOURCE_DIR}/include)

# Add ogg library
target_link_libraries(TEngine PRIVATE ${LIBCURL_OUTPUT_NAME})