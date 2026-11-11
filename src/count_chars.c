#include <stdio.h>

#include "../include/count_chars.h"

int count_chars(FILE *file)
{
    int counter = 0;
    int ch;

    while ((ch = fgetc(file)) != EOF)
    {

        counter++;
    }

    return counter;
}
