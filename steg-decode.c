// steg-decode.c
// Řešení IJC-DU1, příklad b), 12.3.2022
// Autor: Martin Kubička, FIT
// Přeloženo: gcc 7.5

#include "ppm.h"
#include "bitset.h"
#include "eratosthenes.h"
#include "error.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        error_exit("Nesprávny počet argumentov!\n");
    }
    
    struct ppm *var = ppm_read(argv[1]);
    if (var == NULL) {
        error_exit("Chybný formát súboru!\n");
    }

    bitset_alloc(pole, 3*var->xsize*var->ysize);
    unsigned long size = bitset_size(pole);
    Eratosthenes(pole);
    char c = 0;
    int count = 0;
    for (unsigned long i = 2; i < size; i++) {
        if (bitset_getbit(pole, i) == 0 && i >= 29) {	
            c |= ((var->data[i] & 1) << count);
            count++;
            if (count == 8) {
                if (c == '\0') {
                    fprintf(stdout, "%c\n", c);
                    break;
                }
                fprintf(stdout, "%c", c);
                c = 0;
                count = 0;
            }
        }
    }
    if (c != '\0') {
        ppm_free(var);
        bitset_free(pole);
        error_exit("Správa nebola ukončena \\0!\n");
    }
    bitset_free(pole);
    ppm_free(var);
}
