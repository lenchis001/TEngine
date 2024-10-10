file(GLOB_RECURSE sources_files
    "Sources/*.cpp"
    "Sources/*.c"
)

add_library(BmpImageLoadingPlugin SHARED ${sources_files})

target_include_directories(BmpImageLoadingPlugin PUBLIC "Sources" "../../../TEngine/Sources/Components/Graphics/ImageLoading/Plugin")