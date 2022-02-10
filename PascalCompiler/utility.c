#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "tokens.h"

void printfArgs(int *firstFlag, char *format, ...)
{
    if (*firstFlag == 1)
    {
        va_list args;
        va_start(args, format);
        vprintf(format, args);
        va_end(args);
        *firstFlag = 0;
    }
    else
    {
        va_list args;
        va_start(args, format);
        printf("\n");
        vprintf(format, args);
        va_end(args);
    }
}