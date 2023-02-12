cmake_minimum_required(VERSION 3.12)

# set library output path
set(LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../../lib)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/../../lib)

# if(WIN32)
# set(CMAKE_FIND_LIBRARY_SUFFIXES ".dll")
# endif(WIN32)

# if(UNIX)
# set(CMAKE_FIND_LIBRARY_SUFFIXES ".so" ".a")
# endif(UNIX)

# if(MINGW)
# set(CMAKE_FIND_LIBRARY_SUFFIXES ".dll")
# endif(MINGW)

# if(MSVC)
# set(CMAKE_FIND_LIBRARY_SUFFIXES ".dll")
# endif(MSVC)

# if(MSYS)
# set(CMAKE_FIND_LIBRARY_SUFFIXES ".dll")
# endif(MSYS)

# include(${CMAKE_BINARY_DIR}/../../cmake/findsdl.cmake)
find_file(SDL2_INCLUDE_DIR NAMES include HINTS ${CMAKE_BINARY_DIR}/../../deps/SDL2)
find_library(SDL2_LIBRARY NAMES SDL2-2.0 SDL2main HINTS ${LIBRARY_OUTPUT_DIRECTORY} REQUIRED)

include_directories(${SDL2_INCLUDE_DIR})

find_library(opusfile_LIBRARY NAMES opusfile HINTS ${LIBRARY_OUTPUT_DIRECTORY} REQUIRED)
set(opusfile_INCLUDE_PATH ${CMAKE_BINARY_DIR}/../../deps/opusfile/include)

# set(CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR}/../../deps/SDL2/cmake)
# set(SDL2_PATH ${CMAKE_BINARY_DIR}/../../deps/SDL2)

# set(SDL2_INCLUDE_DIR ${CMAKE_BINARY_DIR}/../../deps/SDL2/include)

# file(GLOB_RECURSE SDL2_LIBS LIST_DIRECTORIES false RELATIVE ${CMAKE_BINARY_DIR}/../../lib/ libSDL2*.???)

# message("${SDL2_LIBS}")
# set(SDL2_LIBRARY ${SDL2_LIBS})
# find_package(SDL2 REQUIRED)
add_subdirectory(${CMAKE_BINARY_DIR}/../../deps/SDLMIXER ${BUILD_OUTPUT_PATH})
