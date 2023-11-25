#ifndef CAT_CATFLAGS_H
#define CAT_CATFLAGS_H

#include <string.h>

void CatSetTable(const char *table[static 256]);
void CatMarkEndl(const char *table[static 256]);
void CatMarkTab(const char *table[static 256]);
void CatMarkNonPrintable(const char *table[static 256]);
#endif
