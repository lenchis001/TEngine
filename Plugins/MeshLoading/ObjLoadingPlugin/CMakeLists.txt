file(GLOB_RECURSE sources_files
    "Sources/*.cpp"
    "Sources/*.c"
)

add_library(ObjLoadingPlugin SHARED ${sources_files})

target_include_directories(ObjLoadingPlugin PUBLIC "Sources" "../../../TEngine/Sources/Components/Graphics/MeshLoading/Plugin")

# Copy plugin library to TEngine output directory
add_custom_command(TARGET ObjLoadingPlugin POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    "$<TARGET_FILE:ObjLoadingPlugin>"
    "$<TARGET_FILE_DIR:TEngine>/Plugins/MeshLoading/${CMAKE_SHARED_LIBRARY_PREFIX}ObjLoadingPlugin${CMAKE_SHARED_LIBRARY_SUFFIX}"
)

# Copy plugin library to example output directory
add_custom_command(TARGET ObjLoadingPlugin POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    "$<TARGET_FILE:ObjLoadingPlugin>"
    "$<TARGET_FILE_DIR:Demo>/Plugins/MeshLoading/${CMAKE_SHARED_LIBRARY_PREFIX}ObjLoadingPlugin${CMAKE_SHARED_LIBRARY_SUFFIX}"
)

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