#ifndef COUNT_LONGEST_LINE_H
#define COUNT_LONGEST_LINE_H

typedef struct
{
    int word_count;
    int line_number;

} line_data;

line_data *count_longest_line(FILE *file);
void free_line_data(line_data *file);
#endif