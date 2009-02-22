include_directories(${SDL_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

set(%{APPNAME}_SRCS main.c)
add_executable(%{APPNAME} ${%{APPNAME}_SRCS})
target_link_libraries(%{APPNAME} ${SDL_LIBRARY})
