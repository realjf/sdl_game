cmake_minimum_required(VERSION 3.12)

if(TEST_APP)
    set(PROJECT_NAME sdl_game_test)
else()
    set(PROJECT_NAME sdl_game)
endif()

set(SDLGAME_MAJOR_VERSION 0)
set(SDLGAME_MINOR_VERSION 0)
set(SDLGAME_MICRO_VERSION 1)
set(SDLGAME_VERSION "${SDLGAME_MAJOR_VERSION}.${SDLGAME_MINOR_VERSION}.${SDLGAME_MICRO_VERSION}")

project(${PROJECT_NAME} LANGUAGES C CXX VERSION ${SDLGAME_VERSION})

# if(CMAKE_VERSION VERSION_GREATER 3.12)
# set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)
# endif()
if(POLICY CMP0054)
    cmake_policy(SET CMP0054 NEW)
endif()

# set executable output path
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# set library output path
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

set(CMAKE_VERBOSE_MAKEFILE ON)

include(cmake/common.cmake)
include(cmake/common_macros.cmake)
include(cmake/sdl.cmake)

include_directories(.)
include_directories(deps/SDL2/include)
include_directories(deps/logc/include)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-volatile")

if(TEST_APP)
    SETUP_TEST(${PROJECT_NAME} ${SDLGAME_VERSION})
else()
    SETUP_APP(${PROJECT_NAME} ${SDLGAME_VERSION})
endif()

target_link_libraries(${PROJECT_NAME} sdl2)
