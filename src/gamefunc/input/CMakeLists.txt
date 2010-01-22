include_directories(${SDL_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

set(keyeventinput_lib_SRCS keyeventinput.c)
add_library(keyeventinput ${keyeventinput_lib_SRCS})
