cmake_minimum_required(VERSION 3.15.3)
project(NagyHazi)

set(CMAKE_CXX_STANDARD 11)

add_executable(NagyHazi main.cpp Display.h Display.cpp Vector2D.h Vector2D.cpp ScoreLine.hpp Sprite.h Platform.h Enemy.h Enemy.cpp Character.cpp Character.h Playground.cpp Playground.h Platform.cpp BluePlatform.cpp BluePlatform.h WhitePlatform.cpp WhitePlatform.h FileManager.cpp FileManager.h MenuItem.hpp Menu.hpp memtrace.cpp SDL_Fake.cpp)
INCLUDE(FindPkgConfig)

#ADD_COMPILE_DEFINITIONS(CPORTA)
ADD_COMPILE_DEFINITIONS(MEMTRACE)
#ADD_DEFINITIONS("-Wall -Werror")

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2GFX REQUIRED SDL2_gfx)
PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image)

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2GFX_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2GFX_LIBRARIES} ${SDL2TTF_LIBRARIES} ${SDL2IMAGE_LIBRARIES})
