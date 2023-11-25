#define _GNU_SOURCE
#include <stdio.h>
#include <getopt.h>
#include <stdbool.h>
#include <errno.h>
#include <regex.h>
#include <stdlib.h>


typedef struct { 
    int regex_flag;
    bool invert;
    bool count;
    bool filesMatch;
    bool numberLine;
} Options;

#if 0
Options CatReadFlags (int argc, char *argv[]) {

    int currentFlag = getopt_long(argc, argv, "bevEnstT", longOptions, NULL);
    Options flags = {false, false, false, false, false, false};
    for (;currentFlag != -1
            ; currentFlag = getopt_long(argc, argv, "bevEnstT", longOptions, NULL)) {
        switch (currentFlag) {
        case 'b':
            flags.numberNonBlank = true;
            break; 
        case 'e':
            flags.markEndl = true;
            __attribute__((fallthrough));
        case 'v':
            flags.printNonPrintable = true;
            break; 
        case 'E':
            flags.markEndl = true;
            break; 
        case 'n':
            flags.numberAll = true;
            break; 
        case 's':
            flags.squeeze = true;
            break; 
        case 't':
            flags.printNonPrintable = true;
            __attribute__((fallthrough));
        case 'T':
            flags.tab = true;
        }
    }
    return flags;
}
#endif

void GrepFile(FILE *file, Options flags, regex_t *preg){
    char *line = 0;
    size_t length = 0;
    regmatch_t match;
    (void)flags;
    while(getline(&line, &length, file) > 0) {
        if (!regexec(preg, line, 1, &match, 0)) {
            printf("%s", line);
        } 
    }
    free(line);
}

void Grep(int argc, char *argv[], Options flags) {
    char **pattern = &argv[1];
    char **end = &argv[argc];
    regex_t preg_storage;
    regex_t *preg = &preg_storage;

    for (;pattern != end && pattern[0][0] == '-'; ++pattern)
        ;
    if (pattern == end) {
        fprintf(stderr, "no pattern\n");
        exit(1);
    }
    if (regcomp(preg, *pattern, 0)){
        fprintf(stderr, "failed to compile regex\n");
    }

    for (char **filename = pattern + 1; filename != end; ++filename) {
        if (**filename == '-')
            continue;
        FILE *file = fopen(*filename, "rb");
        if (file == NULL) {
            fprintf(stderr, "%s", argv[0]);
            perror(*filename);
            continue;
        }
        GrepFile(file, flags, preg);
        fclose(file);
    }
}

int main (int argc, char *argv[]) {
    Options flags = {1};
    Grep(argc, argv, flags);
}
