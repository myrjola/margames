set(tetbase_lib_SRCS board.c movement.c tetromino.c)
add_library(tetbase ${tetbase_lib_SRCS})

# m = <math.h> library
target_link_libraries(tetbase m)
