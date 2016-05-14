
#include <stdlib.h>
#include "area51/list.h"
#include "area51/history.h"

/**
 * Initialises a History instance
 * 
 * @param h pointer to History to initialise
 * @param max_age The max_age for entries
 */
void history_init(struct History *h, time_t max_age) {
    list_init(&h->list);
    h->max_age = max_age;
}
