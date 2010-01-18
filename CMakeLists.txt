project(margames)
cmake_minimum_required(VERSION 2.6)


find_package(SDL REQUIRED)
find_package(SDL_image REQUIRED)
find_package(SDL_ttf REQUIRED)

add_subdirectory(src)

INSTALL(DIRECTORY data
        DESTINATION margames)
INCLUDE(CPack)
