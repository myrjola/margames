include_directories(${SDL_INCLUDES}
                    ${CMAKE_CURRENT_BINARY_DIR})

set(martet_SRCS main.c)
add_executable(martet ${margames_SRCS})
target_link_libraries(martet ${SDL_LIBRARY} ${SDLIMAGE_LIBRARY}
                      tetphys tilegfx tetbase keyeventinput gamefuncgfx timer)

add_subdirectory(tetphys)
add_subdirectory(tetgfx)
add_subdirectory(tetbase)
