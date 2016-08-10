
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void backupFile(char *filename) {
    size_t l = strlen(filename) + 3;
    char s[l + 1];
    char t[l + 1];
    for (int i = 9; i > 1; i--) {
        snprintf(s, l, "%s.%d", filename, i - 1);
        snprintf(t, l, "%s.%d", filename, i);
        rename(s, t);
    }

    snprintf(s, l, "%s.%d", filename, 1);
    rename(filename, s);
}
