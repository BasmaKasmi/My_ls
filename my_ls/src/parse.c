// parse.c
#include "parse.h"
#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h> 

// Function to parse command-line arguments and set flags
void parse_args(int argc, char *argv[], Options *options) {
    int opt;
    while ((opt = getopt(argc, argv, "lRdatA")) != -1) {
        switch (opt) {
            case 'l':
                options->long_listing = true;
                break;
            case 'R':
                options->recursive = true;
                break;
            case 'd':
                options->directory = true;
                break;
            // Add cases for other options...
            default:
                fprintf(stderr, "Usage: %s [-lRdatA] [file...]\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }
    // Additional arguments after options are considered as file or directory names
    options->paths = &argv[optind];
    options->num_paths = argc - optind;
}
