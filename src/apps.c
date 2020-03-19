#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/dirent.h"

unsigned int count_delim(const char* str, const char delim);
char** str_to_arr(const char* str, const char delim, const unsigned int occurrences);

int main() {
    const char delim = ';';
    char* path = getenv("PATH");
    char* pathext = getenv("PATHEXT");
    const unsigned int delim_number = count_delim(pathext, delim);
    char** extarr = str_to_arr(pathext, delim, delim_number);

    
    char* path_token = strtok(path, ";");
    while (path_token != NULL) {
        DIR *dir = opendir (path_token);
        if (dir == NULL) continue;
        
        struct dirent* ent;

        
        while ((ent = readdir (dir)) != NULL) {
            
            for (unsigned int i = 0; i < delim_number; i++) {
                if (0 == stricmp(ent->d_name + ent->d_namlen - strlen(extarr[i]), extarr[i])) {
                    printf("%s\n", ent->d_name);
                }
            }
        }

        closedir (dir);

        path_token = strtok (NULL, ";");
    } 

    return 0;
}

unsigned int count_delim(const char* str, const char delim) {
    unsigned int counter = 0;

    for (unsigned int  i = 0; i < strlen(str); i++) {
        if (str[i] == delim) counter++;
    }

    return counter;
}

char** str_to_arr(const char* str, const char delim, const unsigned int occurrences) {
    int delim_number = occurrences > 0 ? occurrences : count_delim(str, delim);
    char** arr = (char**)malloc(sizeof(char*) * (delim_number + 1));

    unsigned int index = 0;
    unsigned int str_pos = 0;
    while(delim_number >= 0) {
        if (str[index] == delim || str[index] == '\0') {
            unsigned int length = index - str_pos;
            arr[delim_number] = (char*)malloc(sizeof(char) *(length + 1));
            char* current = arr[delim_number];
            strncpy(current, str + str_pos, length);
            current[length] = '\0';

            delim_number--;
            str_pos = index + 1;
        }

        index++;
    }

    return arr;
}