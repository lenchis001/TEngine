# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("TEngine")

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_COLOR_MAKEFILE   ON)
set(CMAKE_CXX_STANDARD 17)

if(UNIX AND NOT APPLE)
    set(LINUX TRUE)
endif()

if(LINUX)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread -static-libgcc" )
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -static-libstdc++")
elseif(MSVC)
SET(CMAKE_EXE_LINKER_FLAGS    "${CMAKE_EXE_LINKER_FLAGS} /SAFESEH:NO")
SET(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /SAFESEH:NO")
SET(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} /SAFESEH:NO")
elseif(MINGW)
elseif(APPLE)
endif()

set(CMAKE_CXX_FLAGS_RELEASE "-O3")
if(CMAKE_SYSTEM_PROCESSOR MATCHES "AMD64|x86_64|i[3-6]86")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -msse3")
endif()

set(DEBUG CMAKE_BUILD_TYPE STREQUAL "Debug")

# Include sub-projects.
add_subdirectory("TEngine")
add_subdirectory("Plugins/ImageLoading/BmpImageLoadingPlugin")
add_subdirectory("Plugins/MeshLoading/ObjLoadingPlugin")
add_subdirectory("examples/Demo")
