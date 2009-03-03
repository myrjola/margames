#include "tetphys/tetromino.h"
#include "tetgfx/asciigfx.h"

int main(int argc, char** argv){
    struct Tetromino* a;
    a = tetcreate(TETROMINO_S);
    draw_tetromino_ascii(a);
    tetrotate(a);
    draw_tetromino_ascii(a);
    return 0;
}