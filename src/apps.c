#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/dirent.h"

#define EXE ".exe"
#define BAT ".bat"
#define COM ".com"
#define MSC ".msc"
#define VBS ".vbs"
#define PY ".py"

char* next_str(char* str, const char delim);

int main() {
    char* path = getenv("PATH");
    
    char* path_token = strtok(path, ";");
    while (path_token != NULL) {
        DIR *dir = opendir (path_token);
        if (dir == NULL) continue;
        
        struct dirent* ent;

        char* pathext = getenv("PATHEXT");

        while ((ent = readdir (dir)) != NULL) {
            // char* pathexttekon = next_str(pathext, ';');
            // while(pathexttekon != NULL) {
            //     if (0 == strcmp(ent->d_name + ent->d_namlen - strlen(pathexttekon), pathexttekon)) {
            //         printf("%s\n", ent->d_name);
            //     }

            //     pathexttekon = next_str(pathext, ';');
            // }

            if (0 == strcmp(ent->d_name + ent->d_namlen - strlen(EXE), EXE) ||
                0 == strcmp(ent->d_name + ent->d_namlen - strlen(BAT), BAT) ||
                0 == strcmp(ent->d_name + ent->d_namlen - strlen(COM), COM) ||
                0 == strcmp(ent->d_name + ent->d_namlen - strlen(MSC), MSC) ||
                0 == strcmp(ent->d_name + ent->d_namlen - strlen(VBS), VBS) ||
                0 == strcmp(ent->d_name + ent->d_namlen - strlen(PY), PY) ) {
                printf("%s\n", ent->d_name);
            }
        }

        closedir (dir);

        path_token = strtok (NULL, ";");
    } 

    return 0;
}

char* next_str(char* str, const char delim) {
    unsigned int i = 0;
    for (; i < strlen(str); i++) {
        if (str[i] == delim) break;
    }

    str[i] = '\0';
    str += i;

    return (char*)(str - i);
}