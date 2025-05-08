# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("TEngine")

option(BUILD_DEMO "Build the Demo project" ON)
option(BUILD_ALICE "Build the Alice project" ON)
option(BUILD_WITH_GLFW "Build with GLFW window system" ON)

set(CMAKE_COLOR_MAKEFILE   ON)
set(CMAKE_CXX_STANDARD 17)

if(UNIX AND NOT APPLE)
    set(LINUX TRUE)
endif()

if(LINUX AND NOT ANDROID)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread -static-libgcc" )
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -static-libstdc++")
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
elseif(MSVC)
SET(CMAKE_EXE_LINKER_FLAGS    "${CMAKE_EXE_LINKER_FLAGS} /SAFESEH:NO")
SET(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /SAFESEH:NO")
SET(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} /SAFESEH:NO")
elseif(MINGW)
elseif(APPLE)
enable_language(OBJC)
enable_language(OBJCXX)
endif()

set(CMAKE_CXX_FLAGS_RELEASE "-O3")
if(CMAKE_SYSTEM_PROCESSOR MATCHES "AMD64|x86_64|i[3-6]86")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -msse4.2")
endif()

set(DEBUG CMAKE_BUILD_TYPE STREQUAL "Debug")

# Common dependencies ---------------------------------------------------

# --------------------- Add boost library ---------------------
# Download and configure boost
include(FetchContent)

FetchContent_Declare(
  Boost
  DOWNLOAD_EXTRACT_TIMESTAMP ON
  EXCLUDE_FROM_ALL
  URL https://github.com/boostorg/boost/releases/download/boost-1.84.0/boost-1.84.0.tar.xz
)

set(BOOST_INCLUDE_LIBRARIES filesystem json asio thread)
FetchContent_GetProperties(Boost)

if(NOT Boost_POPULATED)
  FetchContent_Populate(Boost)

  add_subdirectory(${boost_SOURCE_DIR} ${boost_BINARY_DIR})
endif()

# -----------------------------------------------------------------------

# Include sub-projects.
add_subdirectory("TEngine")
add_subdirectory("Plugins/ImageLoading/BmpLoadingPlugin")
add_subdirectory("Plugins/ImageLoading/PngLoadingPlugin")
add_subdirectory("Plugins/MeshLoading/ObjLoadingPlugin")
add_subdirectory("Plugins/MeshLoading/GltfLoadingPlugin")
if(BUILD_DEMO)
add_subdirectory("examples/Demo")
endif()
if(BUILD_ALICE)
add_subdirectory("Editor/Alice")
endif()
