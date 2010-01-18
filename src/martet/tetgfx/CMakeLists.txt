#include_directories(${SDL_INCLUDES}
#                    ${CMAKE_CURRENT_BINARY_DIR})
add_library(asciigfx asciigfx.c)
add_library(fillrectgfx fillrectgfx.c)
add_library(tilegfx tilegfx.c)
INSTALL(TARGETS tilegfx
        DESTINATION margames/lib)
