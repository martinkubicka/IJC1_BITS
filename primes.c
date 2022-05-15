// primes.c
// Řešení IJC-DU1, příklad a), 12.3.2022
// Autor: Martin Kubička, FIT
// Přeloženo: gcc 7.5

#include "bitset.h"
#include "eratosthenes.h"
#include <time.h>
#include <stdio.h>

int main() {
    clock_t start = clock();

    bitset_create(pole, 300000000);
    unsigned long size = bitset_size(pole);
    Eratosthenes(pole);
    
    unsigned long result[10] = {0};
    //count = 9 because we need 10 numbers (0-9)
    int count = 9;
    //getting last 10 prime numbers
    for (unsigned long i = size; i; i--) {
        if (bitset_getbit(pole, i) == 0) {
            result[count] = i;
            count--;
        }
        if (count < 0) {
            break;
        }
    }
    
    for (int i = 0; i < 10; i++) {
        printf("%lu\n", result[i]);
    }
    
    fprintf(stderr, "Time=%.3g\n", (double)(clock()-start)/CLOCKS_PER_SEC);
}
