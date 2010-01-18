#include <string.h>
#include "miscutils.h"

// reverse:  reverse string s
void reverse(char s[])
{
    int i, j;
    char c;

    for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}



/* itoa:  convert n to characters in s */
void itos(int n, char s[])
{
    int i;
    int sign;
    if ((sign = n) < 0)  // if negative...
        n = -n;          // ...make positive
    i = 0;
    do {       // generate digits in reverse order
        s[i++] = n % 10 + '0';   // digits start from '0'
    } while ((n /= 10) > 0);     // delete last digit
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}

