#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "filelogger-int.h"

void filelogger_lock(FileLogger *f) {
    if (f)
        pthread_mutex_lock(&f->mutex);
}

void filelogger_unlock(FileLogger *f) {
    if (f)
        pthread_mutex_unlock(&f->mutex);
}