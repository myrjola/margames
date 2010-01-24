project(martet)

include_directories(${SDL_INCLUDES}
                    ${CMAKE_CURRENT_SOURCE_DIR})
set(tetbase_lib_SRCS board.c movement.c tetromino.c)
add_library(tetbase ${tetbase_lib_SRCS})
add_library(tetgfx tetgfx.c gui.c)

# m = <math.h> library
target_link_libraries(tetbase m)

add_executable(martet main.c)
target_link_libraries(martet ${SDL_LIBRARY} ${SDLIMAGE_LIBRARY} ${SDLTTF_LIBRARY}
                      tetgfx tetbase keyeventinput gamefuncgfx timer miscutils
                      simplemenu score)

INSTALL(TARGETS martet tetbase tetgfx
        RUNTIME DESTINATION bin
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib)