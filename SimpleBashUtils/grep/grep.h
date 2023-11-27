#ifndef GREP_H
#define GREP_H

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define SIZE 1024
#define SIZE_INCREASE 4

const char *error =
    "usage: grep [-e:ivclnhs] [-A num] [-B num] "
    "[-C[num]]\n\t[-e pattern] [-f file] [--binary-files=value] "
    "[--color=when]\n\t[--context[=num]] [--directories=action] [--label] "
    "--line-buffered]\n\t[--null] [pattern] [file ...]\n";

typedef struct {
  int pattern;             // e
  int ignoreCase;          // i
  int invertMatch;         // v
  int countOnly;           // c
  int filesOnly;           // l
  int lineNumber;          // n
  int noFileName;          // h
  int suppressErrors;      // s
  int file;                // f
  int outputMatchedParts;  // o
  int fileNameFlag;
  int isError;
  int errorCode;
  char searchPattern[SIZE_INCREASE * SIZE];
  char fileName[SIZE];
} GrepOptions;

typedef struct {
  int lineCount;
  int MatchCount;
  int printFile;
  int printFlagC;
  int printFlagL;
  char buffer[SIZE];
} GrepLogic;

int GrepWithArgs(char *argv[], int argc, GrepOptions flags);
int GrepReadFlags(int argc, char *argv[], GrepOptions *flags);
void OpenFileWithRegex(GrepOptions *flags, char *filename, char *searchPattern);
void PrintMatchedParts(char *buffer, GrepOptions flags);
void Search(regex_t *regex, GrepOptions flags);

#endif  // GREP_H
