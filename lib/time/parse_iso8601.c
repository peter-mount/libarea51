
#include <stdlib.h>
#include <string.h>

#define _GNU_SOURCE
#include <time.h>

/**
 * Parse an ISO 8601 timestamp of the format "2016-05-26T10:56:20+01:00"
 * or "2016-05-26T09:56:20Z" into a tm structure
 * @param tm
 * @param s
 */
void time_parse_iso8601(struct tm *tm, const char *s) {
    memset(tm, 0, sizeof (struct tm));
    strptime(s, "%FT%T%z", tm);
}
