include_directories(${SDL_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

add_library(timer timer.c)
add_library(miscutils miscutils.c)
add_library(simplemenu simplemenu.c)
