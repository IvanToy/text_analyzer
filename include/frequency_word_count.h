#ifndef FREQUENCY_WORD_COUNT_H
#define  FREQUENCY_WORD_COUNT_H

int frequency_word_count(FILE *file);
int check_word(char **words_array, int *words_freq_count, const char *buffer, int *word_count);

#endif
