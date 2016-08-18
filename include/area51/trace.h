/*
 * A useful macro to include when tracing a line thats causing an error.
 * 
 * useage:
 * 
 * trace;
 * 
 * Generates a line on stdout with the source filename, line number and
 * function name.
 */
#ifndef TRACE_H
#define TRACE_H

#include <area51/log.h>

#define trace logconsole("%s %04d %s",__FILE__,__LINE__,__PRETTY_FUNCTION__)

#endif

