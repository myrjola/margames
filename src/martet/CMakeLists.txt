include_directories(${SDL_INCLUDES}
                    ${CMAKE_CURRENT_BINARY_DIR}
                    ${CMAKE_CURRENT_BINARY_DIR}/tetphys
                    ${CMAKE_CURRENT_BINARY_DIR}/tetgfx)

set(martet_SRCS main.c)
add_executable(martet ${margames_SRCS})
target_link_libraries(martet tetphys asciigfx)

add_subdirectory(tetphys)
add_subdirectory(tetgfx)