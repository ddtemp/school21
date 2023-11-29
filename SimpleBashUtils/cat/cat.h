#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SIZE 4096

typedef struct {
  int numberNonBlank;     // b
  int markEndl;           // e
  int numberAll;          // n
  int squeeze;            // s
  int markTab;            // t
  int printNonPrintable;  // v
} Options;

int CatNoArgs(int fileDescriptor);
int IsFileExist(char *filename);
void PrintFileContent(int argc, char **argv, Options flags);
// void FilesOutput(int argc, char **argv, Options flags, int optind);
Options CatReadFlags(int argc, char *argv[]);
