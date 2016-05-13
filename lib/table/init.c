#include <stdlib.h>
#include <string.h>
#include "area51/list.h"
#include "area51/table.h"

TABLE *table_create() {
    TABLE *t = (TABLE *) malloc(sizeof(TABLE));
    memset(t,0,sizeof(TABLE));
    list_init(&t->rows);
    return t;
}
