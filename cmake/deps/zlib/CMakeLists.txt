cmake_minimum_required(VERSION 3.12)

# set library output path
set(LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../../lib)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/../../lib)

add_subdirectory(${CMAKE_BINARY_DIR}/../../deps/zlib ${BUILD_OUTPUT_PATH})
