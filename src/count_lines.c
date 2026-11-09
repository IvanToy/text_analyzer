#include <stdio.h>

#include "../include/count_lines.h"

#define LINE_FEED 10 // from ASCII table

int count_lines(FILE *file)
{
    int ch;
    int counter = 0;
    int last_char = LINE_FEED;
    while ((ch = fgetc(file)) != EOF)
    {
        if (ch == LINE_FEED)
            counter++;

        last_char = ch;
    }

    if (ferror(file))
        return -1;

    if (feof(file) && last_char != LINE_FEED)
    {
        counter++;
    }

    return counter;
}