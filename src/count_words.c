#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

#include "../include/count_words.h"

int count_words(FILE *file)
{

    int counter = 0;
    char ch;
    bool word_found = false;

    while ((ch = fgetc(file)) != EOF)
    {
        if (isalpha(ch))
        {
            if (!word_found)
            {
                counter++;
                word_found = true;
            }
        }
        else
        {
            word_found = false;
        }
    }

    return counter;
}