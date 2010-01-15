include_directories(${SDL_INCLUDE_DIR} ${SDLTTF_INCLUDE_DIR} ${SDLIMAGE_INCLUDE_DIR}
                    ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_BINARY_DIR}/gamefunc)

set(margames_SRCS main.c)
add_executable(margames ${margames_SRCS})
target_link_libraries(margames ${SDL_LIBRARY} ${SDLIMAGE_LIBRARY} ${SDLTTF_LIBRARY} gamefuncgfx)

add_subdirectory(gamefunc)
add_subdirectory(martet)
