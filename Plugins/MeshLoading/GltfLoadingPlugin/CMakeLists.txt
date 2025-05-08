file(GLOB_RECURSE sources_files
    "Sources/*.cpp"
    "Sources/*.c"
)

add_library(GltfLoadingPlugin SHARED ${sources_files})

target_include_directories(GltfLoadingPlugin PUBLIC "Sources" "../../../TEngine/Sources/Components/Graphics/MeshLoading/Plugin")

# --------------------- Dependencies ---------------------

# Download and configure tinygltf
include(FetchContent)

FetchContent_Declare(
    tinygltf
    GIT_REPOSITORY https://github.com/syoyo/tinygltf.git
    GIT_TAG        v2.9.5
)

FetchContent_GetProperties(tinygltf)
if(NOT tinygltf)
    FetchContent_Populate(tinygltf)
    add_subdirectory(${tinygltf_SOURCE_DIR} ${tinygltf_BINARY_DIR})
endif()

# Set tinygltf as an external project
set_target_properties(tinygltf PROPERTIES FOLDER external)

# Add tinygltf includes
target_include_directories(GltfLoadingPlugin PRIVATE ${tinygltf_SOURCE_DIR})

# --------------------- Add boost library ---------------------
target_link_libraries(
  GltfLoadingPlugin
  PRIVATE Boost::filesystem)