include_directories(${SDL_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

set(margames_SRCS main.c)
add_executable(margames ${margames_SRCS})
target_link_libraries(margames ${SDL_LIBRARY})
