#include <ctype.h>
#include "grep.h"

int main(int argc, char *argv[]) {
  GrepOptions flags = {0};
  if (!GrepReadFlags(argc, argv, &flags))
    GrepWithArgs(argv, argc, flags);
  else
    fprintf(stderr, "%s", error);
  return 0;
}

int GrepReadFlags(int argc, char *argv[], GrepOptions *flags) {
  char buffer[SIZE] = {0};
  if (argc > 2) {
    int currentFlag = getopt(argc, argv, "e:ivclnhsf:o");
    while (currentFlag != -1) {
      switch (currentFlag) {
        case 'e':
          if (!flags->pattern && !flags->file) {
            flags->pattern = 1;
            strcat(flags->searchPattern, optarg);
          } else if (!flags->pattern && flags->file) {
            flags->pattern = 1;
            strcat(flags->searchPattern, "|\0");
            strcat(flags->searchPattern, optarg);
          } else {
            strcat(flags->searchPattern, "|\0");
            strcat(flags->searchPattern, optarg);
          }
          break;
        case 'i':
          flags->ignoreCase = 1;
          break;
        case 'v':
          flags->invertMatch = 1;
          flags->outputMatchedParts = 0;
          break;
        case 'c':
          flags->countOnly = 1;
          break;
        case 'l':
          flags->filesOnly = 1;
          break;
        case 'n':
          flags->lineNumber = 1;
          break;
        case 'h':
          flags->noFileName = 1;
          break;
        case 's':
          flags->suppressErrors = 1;
          break;
        case 'f':
          OpenFileWithRegex(flags, optarg, buffer);
          if (!flags->file && !flags->pattern) {
            flags->file = 1;
            strcat(flags->searchPattern, buffer);
          } else if (!flags->file && flags->pattern) {
            flags->file = 1;
            strcat(flags->searchPattern, "|\0");
            strcat(flags->searchPattern, buffer);
          } else {
            strcat(flags->searchPattern, "|\0");
            strcat(flags->searchPattern, buffer);
          }
          break;
        case 'o':
          if (flags->invertMatch == 0) flags->outputMatchedParts = 1;
          break;
        default: {
          flags->isError = 1;
          flags->errorCode = optopt;
          break;
        }
      }
      currentFlag = getopt(argc, argv, "e:ivclnhsf:o");
    }
  } else {
    flags->isError = 1;
  }
  return flags->isError;
}

void OpenFileWithRegex(GrepOptions *flags, char *filename, char *pattern) {
  FILE *file = fopen(filename, "r");
  if (file == 0) {
    if (!flags->suppressErrors) {
      fprintf(stderr, "s21_grep: %s: No such file or directory\n", filename);
    }
  } else {
    char currentCharacter = '\0';
    char buffer[2] = {'\0'};
    char fileContent[SIZE] = {'\0'};
    while ((currentCharacter = getc(file)) != EOF) {
      buffer[0] = currentCharacter;
      if (buffer[0] == '\n') {
        buffer[0] = '|';
      }
      strcat(fileContent, buffer);
    }
    strcat(pattern, fileContent);
  }
  fclose(file);
}

void PrintMatchedParts(char *buffer, GrepOptions flags) {
  int length = strlen(flags.searchPattern);
  while (*buffer) {
    char *result = NULL;
    if (!flags.ignoreCase) result = strstr(buffer, flags.searchPattern);
    if (flags.ignoreCase) result = strcasestr(buffer, flags.searchPattern);

    if (result == buffer) {
      for (int i = 0; i < length; i++) {
        printf("%c", result[i]);
      }
      printf("\n");
      buffer += length;
    } else {
      buffer++;
    }
  }
}

int GrepWithArgs(char *argv[], int argc, GrepOptions flags) {
  int fileIndex = optind;
  regex_t regex;

  if (!flags.pattern && !flags.file) {
    fileIndex++;
    strcat(flags.searchPattern, argv[optind]);
    regcomp(&regex, flags.searchPattern, 0);
  }
  if (flags.outputMatchedParts || flags.file || flags.pattern)
    regcomp(&regex, flags.searchPattern, REG_EXTENDED);
  if (flags.ignoreCase) regcomp(&regex, flags.searchPattern, REG_ICASE);
  if (argc - fileIndex > 1) flags.fileNameFlag += 1;

  for (int i = fileIndex; i < argc; i++) {
    sprintf(flags.fileName, "%s", argv[i]);
    Search(&regex, flags);
  }

  regfree(&regex);
  return 0;
}

void Search(regex_t *regex, GrepOptions flags) {
  FILE *file = NULL;
  GrepLogic logic = {0};
  file = fopen(flags.fileName, "r");
  int result = 0;

  if (file == NULL) {
    flags.isError = 1;
    if (!flags.suppressErrors) {
      fprintf(stderr, "s21_grep: %s: No such file or directory\n",
              flags.fileName);
    }
  } else {
    while (fgets(logic.buffer, SIZE, file) != NULL && !flags.isError) {
      logic.lineCount++;
      result = regexec(regex, logic.buffer, 0, NULL, 0);

      if (flags.invertMatch && !flags.outputMatchedParts) {
        result = !result;
      }

      if (!result) {
        logic.MatchCount++;

        if (flags.fileNameFlag && !flags.noFileName && !flags.filesOnly &&
            !flags.countOnly) {
          printf("%s:", flags.fileName);
          logic.printFile++;
        }
        if (flags.fileNameFlag && !flags.noFileName && !flags.filesOnly &&
            !flags.countOnly && !logic.printFile) {
          printf("%s:", flags.fileName);
          logic.printFile++;
        }
        if (flags.filesOnly && !flags.countOnly && !logic.printFlagL) {
          printf("%s\n", flags.fileName);
          logic.printFlagL++;
        }
        if (flags.lineNumber && !flags.countOnly && !flags.filesOnly) {
          printf("%d:", logic.lineCount);
        }
        if (!flags.countOnly && flags.outputMatchedParts && !flags.filesOnly) {
          PrintMatchedParts(logic.buffer, flags);
        }
        if (!flags.countOnly && !flags.filesOnly && !flags.outputMatchedParts) {
          printf("%s", logic.buffer);
          if (logic.buffer[strlen(logic.buffer) - 1] != '\n') printf("\n");
        }
      }
    }

    if (flags.fileNameFlag && !logic.printFile && !flags.filesOnly &&
        flags.countOnly) {
      printf("%s:", flags.fileName);
      logic.printFile++;
    }
    if (!logic.printFlagC && flags.countOnly) {
      printf("%d\n", logic.MatchCount);
      logic.printFlagC = 1;
    }
    fclose(file);
  }
}
