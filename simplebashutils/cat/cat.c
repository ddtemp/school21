#include <stdio.h>
#include <getopt.h>
#include <stdbool.h>
#include <errno.h>
#include "headers/CatFlags.h"


typedef struct { 
    bool numberNonBlank;
    bool markEndl;
    bool numberAll;
    bool squeeze;
    bool tab;
    bool printNonPrintable;
} Options;

Options CatReadFlags (int argc, char *argv[]) {
    struct option longOptions[] = {
        {"number-nonblank", 0, NULL, 'b'},
        {"number", 0, NULL, 'n'},
        {"squeeze-blank", 0, NULL, 's'},
        {NULL, 0, NULL, 0}
    };

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

void CatFile(FILE *file, Options flags, const char *table[static 256]){
    
    int currentCharacter = 0;
    int lastCharacter = '\n';
    bool squeeze = false;
    int lineNum = 0;
    
    while (fread(&currentCharacter, 1, 1, file) > 0) {
        if (lastCharacter == '\n'){
            if (flags.squeeze && currentCharacter == '\n') {
                if (squeeze)
                    continue;
                squeeze = true;
            }            
            else
                squeeze = false;

            if (flags.numberNonBlank) {
                if (currentCharacter != '\n')
                    printf("%6i\t", ++lineNum);
            } 
            else if (flags.numberAll) {
                printf("%6i\t", ++lineNum);
            }
        } 
        if (!*table[currentCharacter])
            printf("%c", '\0');
        else
            printf("%s", table[currentCharacter]);
        lastCharacter = currentCharacter;
    }
}

void Cat(int argc, char *argv[], Options flags, const char *table[static 256]) {
    for (char **filename = &argv[1], **end = &argv[argc]; filename != end
            ; ++filename) {
        if (**filename == '-')
            continue;
        
        FILE *file = fopen(*filename, "rb");
        if (file == NULL) {
            fprintf(stderr, "%s", argv[0]);
            perror(*filename);
            continue;
        }
        CatFile(file, flags, table);
        fclose(file);
    }
}

int main (int argc, char *argv[]) {
    
    Options flags = CatReadFlags(argc, argv);
    const char *table[256];
    CatSetTable(table);
    if (flags.markEndl) CatMarkEndl(table);
    if (flags.tab) CatMarkTab(table);
    if (flags.printNonPrintable) CatMarkNonPrintable(table); 
    Cat(argc, argv, flags, table);
}
