project(martet)


add_subdirectory(tetgfx)
add_subdirectory(tetbase)

include_directories(${SDL_INCLUDES}
                    ${CMAKE_CURRENT_SOURCE_DIR})
add_executable(martet main.c)
target_link_libraries(martet ${SDL_LIBRARY} ${SDLIMAGE_LIBRARY} ${SDLTTF_LIBRARY}
                      tilegfx tetbase keyeventinput gamefuncgfx timer miscutils simplemenu)

INSTALL(TARGETS martet
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib)
