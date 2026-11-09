CC = gcc
CFLAGS = -Wall -Wextra -std=c11

TARGET = text_analyzer

SRCS = ./src/replace_target.c \
	   ./src/find_target_in_line.c ./src/count_longest_line.c \
       ./src/count_occurrence.c ./src/count_chars.c \
       ./src/count_words.c ./src/count_lines.c ./src/main.c

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: clean
