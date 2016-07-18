
/* 
 * File:   corpus-import.c
 * Author: peter
 *
 * Created on 17 July 2016, 21:20
 */

#include <stdio.h>
#include <stdlib.h>
#include <networkrail/json.h>
#include <json-c/json.h>

#include <fcntl.h>
#include <elf.h>
#include <sys/mman.h>

#include <sys/types.h>
#include <sys/stat.h>

struct json_object *json_parse_file(int fsock) {
    struct stat sb;

    if (fsock == -1 || fstat(fsock, &sb) == -1) {
        return NULL;
    }

    void *fmap = mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fsock, 0);
    if (fmap == MAP_FAILED) {
        return NULL;
    }

    struct json_object *obj = json_tokener_parse(fmap);

    munmap(fmap, sb.st_size);
    return obj;
}

