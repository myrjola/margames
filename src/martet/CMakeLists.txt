include_directories(${SDL_INCLUDES}
                    ${CMAKE_CURRENT_BINARY_DIR})

set(martet_SRCS main.c)
add_executable(martet ${margames_SRCS})
target_link_libraries(martet tetphys asciigfx tetbase)

add_subdirectory(tetphys)
add_subdirectory(tetgfx)
add_subdirectory(tetbase)
