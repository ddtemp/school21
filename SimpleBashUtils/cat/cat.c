#include "cat.h"

int main(int argc, char *argv[]) {
  if (argc == 1)
    CatNoArgs(STDIN_FILENO);
  else {
    Options flags = CatReadFlags(argc, argv);
    PrintFileContent(argc, argv, flags);
  }
  return 0;
}

int CatNoArgs(int fileDescriptor) {
  char buffer[SIZE];
  int bytesWasRead = 0;
  bytesWasRead = read(fileDescriptor, buffer, SIZE);
  while (bytesWasRead > 0) {
    printf("%.*s", bytesWasRead, buffer);
    bytesWasRead = read(fileDescriptor, buffer, SIZE);
  }
  return bytesWasRead;
}

Options CatReadFlags(int argc, char *argv[]) {
  Options flags = {0, 0, 0, 0, 0, 0};
  const struct option long_options[] = {
      {"number-nonblank", no_argument, &flags.numberNonBlank, 1},
      {"number", no_argument, &flags.numberAll, 1},
      {"squeeze-blank", no_argument, &flags.squeeze, 1},
      {NULL, 0, NULL, 0}};

  int currentFlag = getopt_long(argc, argv, "bevEnstT", long_options, NULL);
  while (currentFlag != -1) {
    switch (currentFlag) {
      case 'b':
        flags.numberNonBlank = 1;
        break;
      case 'e':
        flags.markEndl = 1;
        flags.printNonPrintable = 1;
        break;
      case 'v':
        flags.printNonPrintable = 1;
        break;
      case 'E':
        flags.markEndl = 1;
        break;
      case 'n':
        flags.numberAll = 1;
        break;
      case 's':
        flags.squeeze = 1;
        break;
      case 't':
        flags.printNonPrintable = 1;
        flags.markTab = 1;
        break;
      case 'T':
        flags.markTab = 1;
    }
    currentFlag = getopt_long(argc, argv, "bevEnstT", long_options, NULL);
  }

  if ((flags.numberAll == 1) && (flags.numberNonBlank == 1)) {
    flags.numberAll = 0;
  }

  return flags;
}

void PrintFileContent(int argc, char **argv, Options flags) {
  int isCurrentLineEmpty = 0, isPrevLineEmpty = 0, counter = 0;
  char prevCharacter = '\n';

  for (int i = optind; i < argc; i++) {
    if (IsFileExist(argv[i])) {
      FILE *file = fopen(argv[i], "r");
      int currentCharacter = fgetc(file);
      while (currentCharacter != EOF) {
        if (currentCharacter == '\n' && prevCharacter == '\n') {
          isCurrentLineEmpty = 1;
        } else {
          isCurrentLineEmpty = 0;
        }

        if (!(flags.squeeze && isPrevLineEmpty && isCurrentLineEmpty)) {
          if (prevCharacter == '\n') {
            if (flags.numberAll ||
                (flags.numberNonBlank && !isCurrentLineEmpty)) {
              printf("%6d\t", ++counter);
            }
          }
          if (flags.markEndl && currentCharacter == '\n') {
            printf("$\n");
          } else if (flags.markTab && currentCharacter == '\t') {
            printf("^I");
          } else if (flags.printNonPrintable && currentCharacter < 32 &&
                     currentCharacter != '\n' && currentCharacter != '\t') {
            printf("^%c", currentCharacter + 64);
          } else if (flags.printNonPrintable && currentCharacter == 127) {
            printf("^?");
          } else {
            printf("%c", currentCharacter);
          }
        }
        prevCharacter = currentCharacter;
        isPrevLineEmpty = isCurrentLineEmpty;
        currentCharacter = fgetc(file);
      }
    } else {
      fprintf(stderr, "s21_cat: %s No such file or directory\n", argv[i]);
    }
  }
}

int IsFileExist(char *filename) {
  int result = 0;
  FILE *file = NULL;
  file = fopen(filename, "r");
  if (file != NULL) {
    result = 1;
    fclose(file);
  }
  return result;
}
