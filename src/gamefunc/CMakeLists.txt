include_directories(${SDL_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

set(gamefunc_lib_SRCS imagefunc.c)
add_library(gamefunc ${gamefunc_lib_SRCS})
