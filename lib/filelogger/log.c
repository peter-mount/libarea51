#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "filelogger-int.h"

static const char NL = '\n';

void filelogger_log_r(FileLogger *f, char *s, int o, int l) {
    if (f && s) {
        filelogger_lock(f);
        filelogger_rotate(f);
        fwrite(&s[o], 1, l, f->f);
        if (s[o + l - 1] != NL)
            fwrite(&NL, 1, 1, f->f);

        filelogger_unlock(f);
    }
}

void filelogger_log(FileLogger *f, char *s) {
    if (f && s)
        filelogger_log_r(f, s, 0, strlen(s));
}
