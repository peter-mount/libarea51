#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <area51/hashmap.h>
#include <area51/string.h>

#include <fcntl.h>
#include <elf.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "hashmap-int.h"

/**
 * Read a hashmap from a memory mapped file.
 * 
 * Note: You do not close fsock if this returns 0, otherwise the map will be
 * inconsistent, and you'll probably have a segfault.
 * 
 * The file will be closed when the map is freed.
 * 
 * If this method returns 1, then an error has happened and you should then
 * close the file in that instance.
 * 
 * Also, if you are writing the file later based on updates to the map then
 * you should run backupFile() against the file (which will rename it) before
 * opening the file to write to, otherwise you will cause a segfault.
 * 
 * @param m Hashmap to read into
 * @param r callback to read a record from the file
 * @param f FILE to read from
 */
int hashmapReadMemMap(Hashmap *m, void *(*r)(Hashmap *m, void *p), int fsock) {
    // Only one mapping at a time
    if(m->mmap)
        return 1;
    
    struct stat sb;

    if (fsock == -1 || fstat(fsock, &sb) == -1)
        return 1;

    void *fmap = mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fsock, 0);
    if (fmap == MAP_FAILED)
        return 1;

    m->mmap = fmap;
    m->msize = sb.st_size;
    m->fsock = fsock;
    
    size_t *sp = (size_t *) fmap;
    size_t s = *sp;

    void *p = fmap + sizeof (size_t);
    void *e = fmap + sb.st_size;

    for (int i = 0; p && i < s && p < e; i++) {
        p = r(m, p);
    }

    return 0;
}
