// eratosthenes.c
// Řešení IJC-DU1, příklad a), 12.3.2022
// Autor: Martin Kubička, FIT
// Přeloženo: gcc 7.5

#include "bitset.h"
#include "eratosthenes.h"
#include <math.h>

void Eratosthenes(bitset_t pole) {
    unsigned long size = bitset_size(pole);
    pole[0] = (1UL << (8*sizeof(unsigned long)-1));
    bitset_setbit(pole, 1, 1);
    for (unsigned long i = 2; i <= sqrt(size); i++) {
        if (bitset_getbit(pole, i) == 0) {
            for (unsigned long j = i*2; j <= size; j += i) {
                bitset_setbit(pole, j, 1); 
            }
        }      
    }
}
