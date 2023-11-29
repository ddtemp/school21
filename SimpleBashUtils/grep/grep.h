#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERROR_FILE_NOT_FOUND "s21_grep: %s: No such file or directory\n"

typedef struct {
    int pattern;                // e
    int ignoreCase;             // i
    int invertMatch;            // v
    int countOnlyMatched;       // c
    int onlyMatchedFiles;       // l
    int lineNumber;             // n
    int noFileName;             // h
    int suppressErrors;         // s
    int filePattern;            // f
    int outputMatchedParts;     // o
    int countFiles;
    int numberLine;
    int countMatches;
} Options;

void Grep(char *name, Options config, char *tmpl);
void PrintMainData(char *str, Options *flags, char *tmpl, char *name);
void ConfigF(Options *config, char **template, char *optarg);
void ConfigE(Options *config, char **template, char *optarg);
void ConfigO(regex_t compiledRegex, char *str, Options config);
void PrintAuxData(Options config, char *path);
void *IncreaseLengthStr(void *str, int size);
void SetupConfig(Options *config, int argc);
void AddTemplate(char **str, char *optarg);
int GrepReadFlags (int argc, char **argv, Options *config, char **template);
int CreateTemplate(char **str, char *optarg);
