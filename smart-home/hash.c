#include "hash.h"

int hash(const char *str) {
    unsigned long hash = 5381; // Стандартное начальное значение для DJB2
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }
    return hash;
}