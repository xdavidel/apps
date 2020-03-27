#include "../include/dirent.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LNK_PATTERN ".lnk"
#define START_MENU "\\Microsoft\\Windows\\Start Menu\\Programs"

typedef struct dirent dirent;

unsigned int count_delim(const char *str, const char delim);
char **str_to_arr(const char *str, const char delim,
                  const unsigned int occurrences);
static void search_dir(const char *dirname, const char *pattern);

int main() {
    const char delim = ';';
    char *path = getenv("PATH");
    char *pathext = getenv("PATHEXT");
    char *program_data = getenv("ProgramData");
    char *app_data = getenv("APPDATA");

    char *machine_start_menu = strcat(program_data, START_MENU);
    char *user_start_menu = strcat(app_data, START_MENU);

    const unsigned int delim_number = count_delim(pathext, delim);
    char **extarr = str_to_arr(pathext, delim, delim_number);

    char *path_token = strtok(path, ";");
    while (path_token != NULL) {
        DIR *dir = opendir(path_token);
        if (dir == NULL)
            continue;

        struct dirent *ent;

        while ((ent = readdir(dir)) != NULL) {

            for (unsigned int i = 0; i < delim_number; i++) {
                if (0 ==
                    stricmp(ent->d_name + ent->d_namlen - strlen(extarr[i]),
                            extarr[i])) {
                    printf("%s\\%s\n", path_token,ent->d_name);
                }
            }
        }

        closedir(dir);

        path_token = strtok(NULL, ";");
    }

    // Get links from global start menu
    search_dir(machine_start_menu, LNK_PATTERN);

    // Get links from user start menu
    search_dir(user_start_menu, LNK_PATTERN);

    return 0;
}

unsigned int count_delim(const char *str, const char delim) {
    unsigned int counter = 0;

    for (unsigned int i = 0; i < strlen(str); i++) {
        if (str[i] == delim) {
            counter++;
        }
    }

    return counter;
}

char **str_to_arr(const char *str, const char delim,
                  const unsigned int occurrences) {
    int delim_number = occurrences > 0 ? occurrences : count_delim(str, delim);
    char **arr = (char **)malloc(sizeof(char *) * (delim_number + 1));

    unsigned int index = 0;
    unsigned int str_pos = 0;
    while (delim_number >= 0) {
        if (str[index] == delim || str[index] == '\0') {
            unsigned int length = index - str_pos;
            arr[delim_number] = (char *)malloc(sizeof(char) * (length + 1));
            char *current = arr[delim_number];
            strncpy(current, str + str_pos, length);
            current[length] = '\0';

            delim_number--;
            str_pos = index + 1;
        }

        index++;
    }

    return arr;
}

static void search_dir(const char *dirname, const char *pattern) {
    DIR *dir;
    char buffer[PATH_MAX + 2];
    char *p = buffer;
    const char *src;
    char *end = &buffer[PATH_MAX];
    int ok;

    /* Copy directory name to buffer */
    src = dirname;
    while (p < end && *src != '\0') {
        *p++ = *src++;
    }
    *p = '\0';

    /* Open directory stream */
    dir = opendir(dirname);
    if (dir != NULL) {
        struct dirent *ent;

        /* Print all files and directories within the directory */
        while ((ent = readdir(dir)) != NULL) {
            char *q = p;
            char c;

            /* Get final character of directory name */
            if (buffer < q) {
                c = q[-1];
            } else {
                c = ':';
            }

            /* Append directory separator if not already there */
            if (c != ':' && c != '/' && c != '\\') {
                *q++ = '\\';
            }

            /* Append file name */
            src = ent->d_name;
            while (q < end && *src != '\0') {
                *q++ = *src++;
            }
            *q = '\0';

            /* Decide what to do with the directory entry */
            switch (ent->d_type) {
            case DT_LNK:
            case DT_REG:
                /* Output file name with directory */
                printf("%s\n", buffer);
                break;

            case DT_DIR:
                /* Scan sub-directory recursively */
                if (strcmp(ent->d_name, ".") != 0 &&
                    strcmp(ent->d_name, "..") != 0) {
                    search_dir(buffer, pattern);
                }
                break;

            default:
                /* Ignore device entries */
                /*NOP*/;

                if (0 == stricmp(ent->d_name + ent->d_namlen - strlen(pattern),
                                 pattern)) {
                    printf("%s\n", ent->d_name);
                }
                break;
            }
        }

        closedir(dir);

    } else {
        /* Could not open directory */
        fprintf(stderr, "Cannot open %s (%s)\n", dirname, strerror(errno));
    }
}