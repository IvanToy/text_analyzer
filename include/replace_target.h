#ifndef REPLACE_TARGET_H
#define REPLACE_TARGET_H

int replace_target(FILE *file, char *old_target, char *new_target);
int replace(FILE *temp_file, const char *old_target, const char *new_target, const char *buffer);

#endif