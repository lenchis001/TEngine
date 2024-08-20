file(GLOB_RECURSE sources_files
    "Sources/*.cpp"
    "Sources/*.c"
)

add_library(BmpImageLoadingPlugin SHARED ${sources_files})

target_include_directories(BmpImageLoadingPlugin PUBLIC "Sources" "../../../TEngine/Sources/Components/Graphics/ImageLoading/Plugin")

# Copy plugin library to TEngine output directory
add_custom_command(TARGET BmpImageLoadingPlugin POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    "$<TARGET_FILE:BmpImageLoadingPlugin>"
    "$<TARGET_FILE_DIR:TEngine>/Plugins/ImageLoading/${CMAKE_SHARED_LIBRARY_PREFIX}BmpImageLoadingPlugin${CMAKE_SHARED_LIBRARY_SUFFIX}"
)