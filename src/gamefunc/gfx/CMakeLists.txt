include_directories(${SDL_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

set(gamefuncgfx_lib_SRCS imagefunc.c)
add_library(gamefuncgfx ${gamefuncgfx_lib_SRCS})