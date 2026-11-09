#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#include "../include/count_occurrence.h"

int count_occurrence(FILE *file, char *target, int case_insensitive)
{
    size_t index = 0;
    size_t target_length = strlen(target);

    if (target_length == 0)
    {
        return 0;
    }

    int ch;
    int counter = 0;

    bool is_matched = true;

    while ((ch = fgetc(file)) != EOF)
    {
        if (case_insensitive)
            ch = tolower(ch);

        if (isalpha(ch))
        {

            if (is_matched)
            {
                if (index < target_length &&
                    ch == (case_insensitive
                               ? tolower((unsigned char)target[index])
                               : target[index]))
                {
                    index++;
                }
                else
                {
                    is_matched = false;
                }
            }
        }
        else
        {
            if (is_matched && index == target_length)
            {
                counter++;
            }

            index = 0;
            is_matched = true;
        }
    }

    if (is_matched && index == target_length)
    {
        counter++;
    }

    return counter;
}