
#ifndef AREA51_COMPARATOR_H
#define AREA51_COMPARATOR_H

#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif

    extern int comparator_string(char *, char *);
    extern int comparator_string_caseinsensitive(char *, char *);

    extern int comparator_double(double *, double *);
    extern int comparator_int(int *, int *);
    extern int comparator_long(long*, long *);
    extern int comparator_short(short *, short *);
    extern int comparator_time_t(time_t *, time_t *);


#ifdef __cplusplus
}
#endif

#endif /* AREA51_COMPARATOR_H */

