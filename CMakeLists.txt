CMAKE_MINIMUM_REQUIRED(VERSION 3.10)

# set the project name
PROJECT(WallBreaker)

# add the library
ADD_LIBRARY(WallBreakerLib SHARED Window.h main.c)

# add SDL2,SDL2_image
INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(SDL2 REQUIRED SDL2)
INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS})
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image)
INCLUDE_DIRECTORIES(${SDL2IMAGE_INCLUDE_DIRS})
PKG_SEARCH_MODULE(SDL2GFX REQUIRED SDL2_gfx>=1.0.0)
INCLUDE_DIRECTORIES(${SDL2GFX_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(WallBreakerLib ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2GFX_LIBRARIES})
TARGET_LINK_LIBRARIES(WallBreakerLib m)
ADD_EXECUTABLE(WallBreaker main.c)
TARGET_LINK_LIBRARIES(WallBreaker WallBreakerLib)
