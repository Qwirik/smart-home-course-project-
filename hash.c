#include <stdio.h>
#include <string.h>
#include "hash.h"

// Hash function
void hash(const char *str) {
    unsigned long hash = 5381; // Fixed typo in the initial hash value (5281 -> 5381, which is standard for DJB2 hash)
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }
    return hash;
}
