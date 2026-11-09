#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../include/replace_target.h"

#define BUFFER_SIZE 128

int replace_target(FILE *file, char *old_target, char *new_target)
{

    if (old_target == NULL || old_target[0] == '\0')
    {
        fprintf(stderr, "Search string must not be empty\n");
        return -1;
    }

    FILE *temp_file = fopen("../temp_file.txt", "w");
    if (temp_file == NULL)
    {
        perror("Error opening file");
        return 1;
    }

    size_t capacity = BUFFER_SIZE;
    size_t length = 0;

    char *buffer = malloc(capacity * sizeof(char));
    if (buffer == NULL)
    {
        perror("Failed to allocate memory");
        fclose(temp_file);
        return -1;
    }

    while (fgets(buffer + length, capacity - length, file) != NULL)
    {
        length += strlen(buffer + length);

        if (strchr(buffer, '\n') != NULL)
        {
            replace(temp_file, old_target, new_target, buffer);
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
        replace(temp_file, old_target, new_target, buffer);
    }

    int read_error = ferror(file);
    free(buffer);
    fclose(temp_file);

    return read_error ? -1 : 0;
}

int replace(FILE *temp_file, const char *old_target, const char *new_target, const char *buffer)
{
    const char *cursor = buffer;
    const char *match;

    while ((match = strstr(cursor, old_target)) != NULL)
    {
        size_t bytes = (size_t)(match - cursor);
        if (fwrite(cursor, 1, bytes, temp_file) != bytes)
        {
            return -1;
        }

        if (fputs(new_target, temp_file) == EOF)
        {
            return -1;
        }
        cursor = match + strlen(old_target);
    }

    fputs(cursor, temp_file);

    return 0;
}