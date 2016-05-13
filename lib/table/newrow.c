#include <stdlib.h>
#include <string.h>
#include "area51/list.h"
#include "area51/table.h"

TABLE_ROW *table_newRow(TABLE *t) {
    TABLE_ROW *r = (TABLE_ROW *) malloc(sizeof (TABLE_ROW));
    memset(r, 0, sizeof (TABLE_ROW));
    list_init(&r->cells);
    list_addTail(&t->rows, &r->node);
    return r;
}
