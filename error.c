// error.c
// Řešení IJC-DU1, příklad b), 12.3.2022
// Autor: Martin Kubička, FIT
// Přeloženo: gcc 7.5

#include "error.h"
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

void warning_msg(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    fprintf(stderr, "CHYBA: ");
    vfprintf(stderr, fmt, args);
    va_end(args);
}

void error_exit(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    fprintf(stderr, "CHYBA: ");
    vfprintf(stderr, fmt, args);
    va_end(args);
    exit(1);
}

