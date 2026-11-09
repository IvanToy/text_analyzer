#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../include/find_target_in_line.h"

#define BUFFER_SIZE 128

int find_target_in_line(FILE *file, char *target)
{
    size_t capacity = BUFFER_SIZE;
    size_t length = 0;

    char *buffer = malloc(capacity * sizeof(char));
    if (buffer == NULL)
    {
        perror("Failed to allocate memory");
        return -1;
    }

    int line_count = 0;
    // buffer + length(pointer arithmetic &buffer[length])
    // in fgets, buffer + length  tells fgets() to start writing at index length.
    // in strlen, buffer + length, tells strlen to start counting fro, index length.
    while (fgets(buffer + length, capacity - length, file) != NULL)
    {
        length += strlen(buffer + length);

        if (strchr(buffer, '\n') != NULL)
        {
            line_count++;

            if (strstr(buffer, target) != NULL)
            {
                printf("%d: %s", line_count, buffer);
            }

            length = 0;
        }
        else
        {
            if (length == capacity - 1)
            {
                size_t new_capacity = capacity * 2;
                char *temp = realloc(buffer, new_capacity * sizeof(char));

                if (temp == NULL)
                {
                    perror("Failed to reallocate memory");
                    free(buffer);
                    return -1;
                }

                buffer = temp;
                capacity = new_capacity;
            }
        }
    }

    if (length > 0 && !ferror(file))
    {
        line_count++;

        if (strstr(buffer, target) != NULL)
        {
            printf("%d: %s\n", line_count, buffer);
        }
    }

    int read_error = ferror(file);
    free(buffer);

    return read_error ? -1 : 0;
}
