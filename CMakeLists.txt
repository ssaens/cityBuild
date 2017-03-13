cmake_minimum_required(VERSION 3.6)
project(CityBuild)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp game/game_state.h game/game.h game/game.cpp game/game_state_start.cpp game/game_state_editor.cpp game/game_state_editor.h game/game_state_start.h game/texture_manager.cpp game/texture_manager.h game/animation.cpp game/animation.h world/tile.cpp world/tile.h world/map.cpp world/map.h game/gui.cpp game/gui.h world/City.cpp world/City.h)
add_executable(CityBuild ${SOURCE_FILES})

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(CityBuild ${SFML_LIBRARIES})
endif()