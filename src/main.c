#include <stdio.h>
#include <string.h>

#include "../include/count_lines.h"
#include "../include/count_words.h"
#include "../include/count_chars.h"
#include "../include/count_occurrence.h"
#include "../include/count_longest_line.h"
#include "../include/find_target_in_line.h"
#include "../include/replace_target.h"
#include "../include/frequency_word_count.h"

int main(int argc, char **argv)
{

    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <filename> <command> <optional:flags>", argv[0]);
        return 1;
    }

    const char *command = argv[2];

    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        perror("Error opening file"); // user defined string + : errno (strerr(errno))
        return 1;
    }

    if (strcmp(command, "lines") == 0)
    {
        int lines = count_lines(file);
        printf("Lines: %d\n", lines);
    }

    if (strcmp(command, "words") == 0)
    {
        int words = count_words(file);
        printf("Words: %d\n", words);
    }

    if (strcmp(command, "chars") == 0)
    {
        int ch = count_chars(file);
        printf("Chars: %d\n", ch);
    }

    if (strcmp(command, "find") == 0)
    {
        int case_insensitive = 0;

        if (argc >= 5 && strcmp(argv[4], "-i") == 0)
        {
            case_insensitive = 1;
        }

        int occurrence = count_occurrence(file, argv[3], case_insensitive);

        printf(" occurrence of '%s\n' : %d", argv[3], occurrence);
    }

    if (strcmp(command, "longest") == 0)
    {
        line_data *data = count_longest_line(file);
        printf("Longest line: %d\nLength: %d\n", data->line_number, data->word_count);
        free_line_data(data);
    }

    if (strcmp(command, "contains") == 0)
    {
        if (argc < 4)
        {
            fprintf(stderr, "Error: missing search word\n");
            return 1;
        }

        find_target_in_line(file, argv[3]);
    }

    if (strcmp(command, "replace") == 0)
    {
        if (argc < 5)
        {
            fprintf(stderr, "Error: missing replacement arguments\n");
            return 1;
        }

        if (replace_target(file, argv[3], argv[4]) != 0)
        {
            fprintf(stderr, "Replacement failed\n");
            fclose(file);
            return 1;
        }
    }

    if(strcmp(command, "frequency") == 0){

      if(frequency_word_count(file) != 0){
          fprintf(stderr, "Failed to calculate frequency");
          fclose(file);
          return 1;
      }
    }

    fclose(file);
    return 0;
}
