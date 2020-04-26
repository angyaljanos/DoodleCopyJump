cmake_minimum_required(VERSION 3.15.3)
project(NagyHazi)

set(CMAKE_CXX_STANDARD 14)

add_executable(NagyHazi main.cpp Display.h Display.cpp Vector2D.h Vector2D.cpp ScoreLine.h ScoreLine.cpp Sprite.h Platform.h Enemy.h Enemy.cpp Character.cpp Character.h Playground.cpp Playground.h Platform.cpp BluePlatform.cpp BluePlatform.h WhitePlatform.cpp WhitePlatform.h)
INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2GFX REQUIRED SDL2_gfx)
PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf)

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2GFX_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2GFX_LIBRARIES} ${SDL2TTF_LIBRARIES} ${SDL2IMAGE_LIBRARIES})
