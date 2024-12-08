file(GLOB_RECURSE sources_files
    "Sources/*.cpp"
    "Sources/*.c"
)

add_library(BmpLoadingPlugin SHARED ${sources_files})

target_include_directories(BmpLoadingPlugin PUBLIC "Sources" "../../../TEngine/Sources/Components/Graphics/ImageLoading/Plugin")