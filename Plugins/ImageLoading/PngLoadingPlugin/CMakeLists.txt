file(GLOB_RECURSE sources_files
    "Sources/*.cpp"
    "Sources/*.c"
)

add_library(PngLoadingPlugin SHARED ${sources_files})

target_include_directories(PngLoadingPlugin PUBLIC "Sources" "../../../TEngine/Sources/Components/Graphics/ImageLoading/Plugin")

# --------------------- Dependencies ---------------------

# Download and configure libpng
include(FetchContent)

FetchContent_Declare(
    libpng
    GIT_REPOSITORY git@github.com:pnggroup/libpng.git
    GIT_TAG        v1.6.44
    GIT_SHALLOW    TRUE
)

FetchContent_GetProperties(libpng)

set(PNG_SHARED OFF CACHE BOOL "" FORCE)
set(PNG_TESTS OFF CACHE BOOL "" FORCE)
set(PNG_TOOLS OFF CACHE BOOL "" FORCE)
set(PNG_EXECUTABLES OFF CACHE BOOL "" FORCE)

if(NOT libpng_POPULATED)
    FetchContent_Populate(libpng)
    add_subdirectory(${libpng_SOURCE_DIR} ${libpng_BINARY_DIR})
endif()

# Add libpng includes
target_include_directories(PngLoadingPlugin PRIVATE ${libpng_SOURCE_DIR} ${libpng_BINARY_DIR})

# Add libpng library
target_link_libraries(PngLoadingPlugin PRIVATE png_static)

# Add libpng dependencies
add_dependencies(PngLoadingPlugin pnglibconf_h pnglibconf_out png_static)