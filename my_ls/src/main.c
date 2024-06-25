#include <stdio.h>
#include "list.h"
#include "parse.h"

int main(int argc, char *argv[]) {
    Options options = {0}; // Initialize all options to false/0.

    // Assume you have a function in parse.c that initializes the options based on argc and argv
    parse_args(argc, argv, &options);

    // If no paths are given, use the current directory "."
    if (options.num_paths == 0) {
        list_directory(".", &options);
    } else {
        // Otherwise, list each directory passed as an argument
        for (int i = 0; i < options.num_paths; ++i) {
            list_directory(options.paths[i], &options);
        }
    }

    return 0;
}
