file(GLOB_RECURSE sources_files
    "Sources/*.cpp"
    "Sources/*.c"
)

add_library(ObjLoadingPlugin SHARED ${sources_files})

target_include_directories(ObjLoadingPlugin PUBLIC "Sources" "../../../TEngine/Sources/Components/Graphics/MeshLoading/Plugin")

# --------------------- Dependencies ---------------------

# Download and configure RapidObj
include(FetchContent)

FetchContent_Declare(
    rapidobj
    GIT_REPOSITORY https://github.com/guybrush77/rapidobj.git
    GIT_TAG        master
)

FetchContent_GetProperties(rapidobj)
if(NOT rapidobj_POPULATED)
    FetchContent_Populate(rapidobj)
    add_subdirectory(${rapidobj_SOURCE_DIR} ${rapidobj_BINARY_DIR})
endif()

# Set RapidObj as an external project
set_target_properties(rapidobj PROPERTIES FOLDER external)

# Add RapidObj includes
target_include_directories(ObjLoadingPlugin PRIVATE ${rapidobj_SOURCE_DIR}/include)

# Add RapidObj library
target_link_libraries(ObjLoadingPlugin PRIVATE rapidobj)

# --------------------- Add boost library ---------------------
target_link_libraries(
  ObjLoadingPlugin
  PRIVATE Boost::filesystem)