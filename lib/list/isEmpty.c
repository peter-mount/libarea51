
#include <stdlib.h>
#include "area51/list.h"

int list_isEmpty( struct List *l )
{
    return l->l_head->n_succ==NULL ? 1 : 0;
}
