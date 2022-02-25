#include "e1A.h"
#include <string.h>

int is_prefix(const char* s, const char* t) {
    while (*s && *t && *s == *t) { s++; t++; }
    return *s == 0;
}
