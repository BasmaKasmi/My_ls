#ifndef PARSE_H
#define PARSE_H

#include <stdbool.h>

// Struct to store command-line options
typedef struct {
    bool long_listing;   // Corresponds to -l
    bool recursive;      // Corresponds to -R
    bool directory;      // Corresponds to -d
    bool show_all;       // Corresponds to -a
    bool show_almost_all;// Corresponds to -A
    // Add more options if necessary
    char **paths;        // Array of paths to apply ls operation
    int num_paths;       // Number of paths
} Options;

// Function to parse command-line arguments and set flags
void parse_args(int argc, char *argv[], Options *options);

#endif /* PARSE_H */
