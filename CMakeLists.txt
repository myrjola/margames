project(margames)
cmake_minimum_required(VERSION 2.6)


find_package(SDL REQUIRED)
find_package(SDL_image REQUIRED)
find_package(SDL_ttf REQUIRED)

add_subdirectory(src)

INSTALL(DIRECTORY data
        DESTINATION .)
INCLUDE(CPack)
INCLUDE(InstallRequiredSystemLibraries)

IF(WIN32)
# Commented out because of cross compiling.
#     INSTALL(FILES
#         c:/WINDOWS/system32/SDL.dll
#         c:/WINDOWS/system32/SDL_image.dll
#         c:/WINDOWS/system32/SDL_ttf.dll
#     DESTINATION margames/bin
#     )
ENDIF(WIN32)

SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Making some simple games for fun and experience.")
SET(CPACK_PACKAGE_VENDOR "Martin Yrjölä")
SET(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/README")
SET(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
SET(CPACK_PACKAGE_VERSION_MAJOR "0")
SET(CPACK_PACKAGE_VERSION_MINOR "1")
SET(CPACK_PACKAGE_VERSION_PATCH "0")
SET(CPACK_PACKAGE_INSTALL_DIRECTORY "CMake ${CMake_VERSION_MAJOR}.${CMake_VERSION_MINOR}")
IF(WIN32 AND NOT UNIX)
  # There is a bug in NSI that does not handle full unix paths properly. Make
  # sure there is at least one set of four (4) backlasshes.
  SET(CPACK_NSIS_DISPLAY_NAME "${CPACK_PACKAGE_INSTALL_DIRECTORY} Martet")
  SET(CPACK_NSIS_HELP_LINK "http:\\\\\\\\github.com/yrjoelae/margames\#")
  SET(CPACK_NSIS_URL_INFO_ABOUT "http:\\\\\\\\github.com/yrjoelae/margames\#")
  SET(CPACK_NSIS_CONTACT "martin.yrjola@gmail.com")
  SET(CPACK_NSIS_MODIFY_PATH ON)
ENDIF(WIN32 AND NOT UNIX)
