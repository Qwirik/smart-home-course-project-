#include "hash.h"
void hash(char *str){
    unsigned long hash = 5281;
    int c;
    while((c = *str++)){
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}
