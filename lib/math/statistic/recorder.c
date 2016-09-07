#include <stdlib.h>
#include <limits.h>
#include <pthread.h>
#include <area51/charbuffer.h>
#include <area51/curl.h>
#include <area51/json.h>
#include <area51/log.h>
#include <area51/main.h>
#include <area51/math.h>
#include <string.h>

#include "area51/list.h"

#define TIMESTAMP_LEN 31

struct logging {
    // Source statistic
    struct Statistic *src;
    // Flags on what to reset
    int flags;
    // Last value
    struct Statistic stat;
    time_t time;
    struct tm tm;
    // Timestamp as YYYY-MM-DD HH:MM;SS (in GMT)
    char timestamp[TIMESTAMP_LEN + 1];
    // ISO timestamp YYYY-MM-DDTHH:MM:SSZ
    char iso[TIMESTAMP_LEN + 1];
    // Name of this statistic
    char *name;
    // Log to console
    bool log;
    // List of HTTP GET URL's to post to
    List get;
};

static void sendGet(char *path, struct logging *l) {
    CharBuffer *b = charbuffer_new();
    if (b) {
        charbuffer_append(b, path);
        charbuffer_replace_int(b, "{count}", l->stat.count);
        charbuffer_replace_int(b, "{max}", l->stat.max);
        charbuffer_replace_int(b, "{min}", l->stat.min);
        charbuffer_replace_int(b, "{total}", l->stat.total);
        charbuffer_replace_int(b, "{value}", l->stat.value);
        charbuffer_replace(b, "{timestamp}", l->timestamp);
        charbuffer_replace(b, "{iso}", l->iso);
        int len;
        char *url = charbuffer_tostring(b, &len);
        curl_get(url, b);
        free(url);
        charbuffer_free(b);
    }
}

static void logStats(MainTask *t) {
    struct logging *l = area51_mainGetUserData(t);

    // get & reset the statistic
    statistic_reset_r(l->src, &l->stat, l->flags);
    time(&l->time);
    gmtime_r(&l->time, &l->tm);
    snprintf(l->timestamp, TIMESTAMP_LEN,
            "%04d-%02d-%02d%%20%02d:%02d:%02d",
            l->tm.tm_year + 1900, l->tm.tm_mon + 1, l->tm.tm_mday,
            l->tm.tm_hour, l->tm.tm_min, l->tm.tm_sec);
    snprintf(l->iso, TIMESTAMP_LEN,
            "%04d-%02d-%02dT%02d:%02d:%02dZ",
            l->tm.tm_year + 1900, l->tm.tm_mon + 1, l->tm.tm_mday,
            l->tm.tm_hour, l->tm.tm_min, l->tm.tm_sec);

    if (l->log)
        logconsole("%s value %d count %d max %d min %d total %d",
            l->name,
            l->stat.value,
            l->stat.count,
            l->stat.max,
            l->stat.min,
            l->stat.total);

    // HTTP Get submissions
    Node *n = list_getHead(&l->get);
    while (list_isNode(n)) {
        sendGet(n->name, l);
        n = list_getNext(n);
    }

}

void statistic_recorder(MainTasks *main, struct Statistic *s, struct json_object *obj) {
    struct logging *logging = malloc(sizeof (struct logging));
    if (logging) {
        memset(logging, 0, sizeof (struct logging));
        list_init(&logging->get);
        statistic_init(&logging->stat);

        logging->src = s;

        char *str = json_getString(obj, "reset");
        if (str) {
            if (strcasecmp(str, "none") == 0)
                logging->flags = STAT_RESET_NONE;
            else if (strcasecmp(str, "all") == 0)
                logging->flags = STAT_RESET_ALL;
            else if (strcasecmp(str, "minmax") == 0)
                logging->flags = STAT_RESET_MINMAX;
            else if (strcasecmp(str, "value") == 0)
                logging->flags = STAT_RESET_VALUE | STAT_RESET_COUNT | STAT_RESET_TOTAL;
            else
                logging->flags = STAT_RESET_ALL;
        } else logging->flags = STAT_RESET_ALL;

        if (json_getString(obj, "minmax"))
            logging->flags |= STAT_CALCULATE_MINMAX;

        str = json_getString(obj, "name");
        if (str)
            logging->name = strdup(str);
        if (!logging->name)
            logging->name = "";

        // Log to the console
        logging->log = json_getBoolean(obj, "log");

        struct json_object *o;
        if (json_object_object_get_ex(obj, "http.get", &o)) {
            struct array_list *list = json_object_get_array(o);
            int len = array_list_length(list);
            for (int i = 0; i < len; i++) {
                str = (char *) json_object_get_string((json_object *) array_list_get_idx(list, i));
                if (str)
                    str = strdup(str);
                if (str) {
                    Node *n = node_alloc(str);
                    if (n)
                        list_addTail(&logging->get, n);
                }
            }
        }

        // Update period & schedule the update
        int period = json_getInt(obj, "period");
        if (period < 1)
            period = 60;
        area51_mainRunPeriodic(main, logStats, period, logging, NULL);
    }
}