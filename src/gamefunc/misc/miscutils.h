#include <string.h>

#include "SDL/SDL.h"

#ifndef MISCUTILS_H_
#define MISCUTILS_H_

// reverse:  Reverse string s.
void reverse(char[]);

// itoa:  Convert n to characters in s.
void itos(int n, char* s);

#endif