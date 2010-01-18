set(tetphys_lib_SRCS tetromino.c movement.c)
add_library(tetphys ${tetphys_lib_SRCS})

# m = <math.h> library
target_link_libraries(tetphys m)
INSTALL(TARGETS tetphys
        DESTINATION margames/lib)
