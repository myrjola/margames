include_directories(${SDL_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

set(timer_lib_SRCS timer.c)
add_library(timer ${timer_lib_SRCS})
add_library(miscutils miscutils.c)