#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <stdint.h>
#include <string.h>

#include "../include/frequency_word_count.h"
#include "../include/count_words.h"

#define BUFFER_SIZE 128

int frequency_word_count(FILE *file){

    int total_words = 0;
	int word_count = 0;
	int exit_status = EXIT_FAILURE;

	int *words_freq_count = NULL;
	char **words_array = NULL;
	char *buffer = NULL;


	total_words = count_words(file);

	if (total_words > 0) {

		words_array = malloc(total_words * sizeof(*words_array));

		if (words_array == NULL) {
			perror("Failed to allocate memory");
			goto cleanup;
		}

		words_freq_count = calloc(total_words, sizeof(*words_freq_count));

		if (words_freq_count == NULL) {
			perror("Failed to allocate memory");
			goto cleanup;
		}
	}

	size_t capacity = BUFFER_SIZE;
	size_t index_buffer = 0;

	buffer = malloc(capacity);

	if (buffer == NULL) {
		perror("Failed to allocate memory");
		goto cleanup;
	}

	if (fseek(file, 0, SEEK_SET) != 0) {
    perror("Failed to rewind file");
    goto cleanup;
	}

	int ch;
	while((ch = fgetc(file)) != EOF){

	    if(isalpha(ch)){

					if (index_buffer + 1 >= capacity) {

						if (capacity > SIZE_MAX / 2) {
							fprintf(stderr, "Buffer size overflow\n");
							goto cleanup;
						}

						size_t new_capacity = capacity * 2;

						char *temp_buffer = realloc(buffer, new_capacity);

						if (temp_buffer == NULL) {
							perror("Failed to allocate memory");
							goto cleanup;
						}

						buffer = temp_buffer;
						capacity = new_capacity;
					}

						buffer[index_buffer++] = ch;
		}else{
		    if (index_buffer > 0) {

				buffer[index_buffer] = '\0';

				if (check_word(words_array, words_freq_count, buffer, &word_count) != 0) {
				    goto cleanup;
				}
			    index_buffer = 0;
			}

		}
	}



	if (ferror(file)) {
    perror("Error reading file");
    goto cleanup;
	}

	if (index_buffer > 0) {

		buffer[index_buffer] = '\0';

		if (check_word(words_array, words_freq_count, buffer, &word_count) != 0) {
			goto cleanup;
		}
	}



	for (int i = 0; i < word_count; i++) {
		printf("%s: %d\n", words_array[i], words_freq_count[i]);
	}

	exit_status = EXIT_SUCCESS;

	cleanup:

		for (int i = 0; i < word_count; i++) {
			free(words_array[i]);
		}

	free(words_array);
	free(words_freq_count);
	free(buffer);

	return exit_status;
}


int check_word(char **words_array, int *words_freq_count, const char *buffer, int *word_count){

   	for (int i = 0; i < *word_count; i++) {

		if (strcmp(words_array[i], buffer) == 0) {
			words_freq_count[i]++;
			return 0;
		}
	}

   	char *new_word = malloc(strlen(buffer) + 1);

	if (new_word == NULL) {
		perror("Failed to allocate memory");
		return 1;
	}

	strcpy(new_word, buffer);

	words_array[*word_count] = new_word;
	words_freq_count[*word_count] = 1;
	(*word_count)++;

	return 0;
}
