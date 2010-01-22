project(martet)


add_subdirectory(tetgfx)
add_subdirectory(tetbase)

include_directories(${SDL_INCLUDES}
                    ${CMAKE_CURRENT_SOURCE_DIR})
add_executable(martet main.c)
target_link_libraries(martet ${SDL_LIBRARY} ${SDLIMAGE_LIBRARY} ${SDLTTF_LIBRARY}
                      tilegfx tetbase keyeventinput gamefuncgfx timer miscutils simplemenu)

INCLUDE(GetPrerequisites)
get_prerequisites(${CMAKE_CURRENT_BINARY_DIR}/martet martet_dependencies 0 1 .
                  ${CMAKE_CURRENT_SOURCE_DIR})
INSTALL(TARGETS martet
        RUNTIME DESTINATION bin
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib)

INSTALL(FILES ${martet_dependencies}
        DESTINATION bin)