/* 
 * File:   string.h
 * Author: Peter T Mount
 *
 * Created on March 26, 2014, 4:58 PM
 */

#ifndef AREA51_FILE_H
#define	AREA51_FILE_H

#include <sys/types.h>

#ifdef	__cplusplus
extern "C" {
#endif

    extern int mkdirs(char *path, mode_t nmode);

#ifdef	__cplusplus
}
#endif

#endif	/* FILE_H */

