#include <stdlib.h>
#include <stdio.h>

#include "../include/count_longest_line.h"

#define LINE_FEED 10

line_data *count_longest_line(FILE *file)
{
    line_data *data = malloc(sizeof(*data));
    if (data == NULL)
    {
        perror("Failed to allocate memory");
        return NULL;
    }

    int ch;

    int line_num = 0, word_count = 0, temp_word = 0;
    int temp_line = 1;

    while ((ch = fgetc(file)) != EOF)
    {
        if (ch != LINE_FEED)
        {
            temp_word++;
        }
        else
        {

            if (temp_word > word_count)
            {
                word_count = temp_word;
                line_num = temp_line;
            }
            temp_word = 0;
            temp_line++;
        }
    }

    if (temp_word > word_count)
    {
        word_count = temp_word;
        line_num = temp_line;
    }

    data->line_number = line_num;
    data->word_count = word_count;

    return data;
}

void free_line_data(line_data *data)
{
    free(data);
}