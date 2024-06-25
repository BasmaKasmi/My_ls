#include "list.h"
#include <pwd.h> 
#include <grp.h>
#include <time.h>

// Implement get_mode_string to return a string representing the file mode
char *get_mode_string(mode_t mode) {
    static char mode_str[11];
    snprintf(mode_str, sizeof(mode_str), "%c%c%c%c%c%c%c%c%c%c",
        S_ISDIR(mode) ? 'd' : S_ISLNK(mode) ? 'l' : '-',
        mode & S_IRUSR ? 'r' : '-', mode & S_IWUSR ? 'w' : '-',
        mode & S_IXUSR ? 'x' : '-', mode & S_IRGRP ? 'r' : '-',
        mode & S_IWGRP ? 'w' : '-', mode & S_IXGRP ? 'x' : '-',
        mode & S_IROTH ? 'r' : '-', mode & S_IWOTH ? 'w' : '-',
        mode & S_IXOTH ? 'x' : '-');
    return mode_str;
}

// Implement display_detailed_info to print detailed information about the file
void display_detailed_info(const char *path, const char *file_name) {
    struct stat file_stat;
    char full_path[PATH_MAX];
    snprintf(full_path, PATH_MAX, "%s/%s", path, file_name);

    if (lstat(full_path, &file_stat) != 0) {
        perror("lstat");
        return;
    }

    printf("%s ", get_mode_string(file_stat.st_mode));
    printf("%lu ", (unsigned long)file_stat.st_nlink);
    printf("%s ", getpwuid(file_stat.st_uid)->pw_name);
    printf("%s ", getgrgid(file_stat.st_gid)->gr_name);
    printf("%5ld ", (long)file_stat.st_size);

    char time_buff[30];
    const struct tm *timeinfo = localtime(&file_stat.st_mtime);
    strftime(time_buff, sizeof(time_buff), "%b %d %H:%M", timeinfo);
    printf("%s ", time_buff);

    printf("%s\n", file_name);
}


// Helper function to print file permissions
void print_permissions(mode_t mode) {
    printf( (S_ISDIR(mode)) ? "d" : "-");
    printf( (mode & S_IRUSR) ? "r" : "-");
    printf( (mode & S_IWUSR) ? "w" : "-");
    printf( (mode & S_IXUSR) ? "x" : "-");
    printf( (mode & S_IRGRP) ? "r" : "-");
    printf( (mode & S_IWGRP) ? "w" : "-");
    printf( (mode & S_IXGRP) ? "x" : "-");
    printf( (mode & S_IROTH) ? "r" : "-");
    printf( (mode & S_IWOTH) ? "w" : "-");
    printf( (mode & S_IXOTH) ? "x" : "-");
}

// Function to print file details
void print_file_details(const char *path, const struct dirent *entry) {
    struct stat file_stat;
    char full_path[PATH_MAX];

    snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);
    if (lstat(full_path, &file_stat) < 0) {
        perror("lstat");
        return;
    }

    // Print file permissions
    print_permissions(file_stat.st_mode);

    // Print number of hard links
    printf(" %lu", file_stat.st_nlink);

    // Print file owner and group
    printf(" %s %s", getpwuid(file_stat.st_uid)->pw_name, getgrgid(file_stat.st_gid)->gr_name);

    // Print file size
    printf(" %lld", (long long)file_stat.st_size);

    // Print last modification time
    char time_str[256];
    strftime(time_str, sizeof(time_str), "%b %d %H:%M", localtime(&file_stat.st_mtime));
    printf(" %s", time_str);

    // Print file name
    printf(" %s\n", entry->d_name);
}

// Main function to list directory
void list_directory(const char *path, const Options *options) {
    DIR *dir = opendir(path);
    struct dirent *entry;

    if (!dir) {
        perror("opendir");
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        // Skip hidden files if the show_all flag is not set
        if (!options->show_all && entry->d_name[0] == '.') {
            continue;
        }

        // If the long_listing flag is set, print the details
        if (options->long_listing) {
            print_file_details(path, entry);
        } else {
            // Otherwise, just print the name
            printf("%s\n", entry->d_name);
        }

        // Handle recursive listing if the flag is set
        if (options->recursive && entry->d_type == DT_DIR) {
            // Skip '.' and '..' to prevent infinite recursion
            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
                char next_path[PATH_MAX];
                snprintf(next_path, sizeof(next_path), "%s/%s", path, entry->d_name);
                list_directory(next_path, options);
            }
        }
    }

    closedir(dir);
}
