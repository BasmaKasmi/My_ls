// list.h
#ifndef LIST_H
#define LIST_H

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <limits.h>
#include <stdbool.h>
#include "parse.h"

void list_directory(const char *path, const Options *options);
void display_detailed_info(const char *path, const char *file_name);
char *get_mode_string(mode_t mode);

#endif /* LIST_H */
