cmake_minimum_required(VERSION 3.12)

set(PROJECT_ROOT_PATH ../)

set(SDLGAME_MAJOR_VERSION 0)
set(SDLGAME_MINOR_VERSION 0)
set(SDLGAME_MICRO_VERSION 1)
set(SDLGAME_VERSION "${SDLGAME_MAJOR_VERSION}.${SDLGAME_MINOR_VERSION}.${SDLGAME_MICRO_VERSION}")

# if(CMAKE_VERSION VERSION_GREATER 3.12)
# set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)
# endif()
if(POLICY CMP0054)
    cmake_policy(SET CMP0054 NEW)
endif()

# set executable output path
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../bin_test)

# set library output path
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../lib)

set(CMAKE_VERBOSE_MAKEFILE ON)

include(${PROJECT_ROOT_PATH}cmake/common.cmake)
include(${PROJECT_ROOT_PATH}cmake/comm_macros.cmake)

# sdl
# include(${PROJECT_ROOT_PATH}cmake/findsdl.cmake)
include_directories(.)
include_directories(./include)
include_directories(${PROJECT_ROOT_PATH}deps/SDL2/include)
include_directories(${PROJECT_ROOT_PATH}deps/logc/include)
include_directories(${PROJECT_ROOT_PATH}deps/SDLIMG)
include_directories(${PROJECT_ROOT_PATH}deps/SDLTTF)
include_directories(${PROJECT_ROOT_PATH}deps/tinyxml)
include_directories(${PROJECT_ROOT_PATH}deps/base64)
include_directories(${PROJECT_ROOT_PATH}deps/zlib)
include_directories(${PROJECT_ROOT_PATH}deps/SDLMIXER/include)

# include_directories(${SDL2_INCLUDE_DIR})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-volatile -g")

# add_subdirectory(hello)
# add_subdirectory(game_class)
# add_subdirectory(sdl_texture)
# add_subdirectory(anim_sprite)
# add_subdirectory(sdl_image)
# add_subdirectory(texture_mgr)
# add_subdirectory(game_obj)
# add_subdirectory(game_obj_polymorphism)
# add_subdirectory(vector2d_joysticks)
# add_subdirectory(vector2d_joystick_button)
# add_subdirectory(vector2d_mouse_keyboard)
# add_subdirectory(state_machine)
# add_subdirectory(menu_state)
# add_subdirectory(pause_state)
# add_subdirectory(game_over_state)
# add_subdirectory(xml_object_factories)
# add_subdirectory(tiled_map)
# add_subdirectory(tiled_map_obj_layer)
add_subdirectory(sound)
