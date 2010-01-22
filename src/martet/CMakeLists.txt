project(martet)

add_subdirectory(tetgfx)
add_subdirectory(tetbase)

include_directories(${SDL_INCLUDES}
                    ${CMAKE_CURRENT_SOURCE_DIR})
set(tetbase_lib_SRCS board.c movement.c tetromino.c)
add_library(tetbase ${tetbase_lib_SRCS})
add_library(tilegfx tilegfx.c)

# m = <math.h> library
target_link_libraries(tetbase m)

add_executable(martet main.c)
target_link_libraries(martet ${SDL_LIBRARY} ${SDLIMAGE_LIBRARY} ${SDLTTF_LIBRARY}
                      tilegfx tetbase keyeventinput gamefuncgfx timer miscutils simplemenu)

INCLUDE(GetPrerequisites)
get_prerequisites(${CMAKE_CURRENT_BINARY_DIR}/martet martet_dependencies 1 1 .
                  ${CMAKE_CURRENT_SOURCE_DIR})
MESSAGE("${martet_dependencies}")
INSTALL(TARGETS martet tetbase tilegfx
        RUNTIME DESTINATION bin
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib)

INSTALL(FILES ${martet_dependencies}
        DESTINATION bin)