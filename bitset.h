// bitset.h
// Řešení IJC-DU1, příklad a), 12.3.2022
// Autor: Martin Kubička, FIT
// Přeloženo: gcc 7.5

#include "error.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>

#ifndef BITSET_H
#define BITSET_H

typedef unsigned long bitset_t[];

typedef unsigned long bitset_index_t;

#define bitset_create(jmeno_pole, velikost) _Static_assert(velikost > 0, "Veľkosť musí byť väčšia ako 0!\n"); \
                                            unsigned long jmeno_pole[velikost/(8*sizeof(unsigned long)) + (velikost%(8*sizeof(unsigned long))?1:0)] = {0}; \
                                            jmeno_pole[0] = sizeof(jmeno_pole)*8;

#define bitset_alloc(jmeno_pole, velikost)  assert(velikost > 0); \
                                            unsigned long *jmeno_pole = calloc((velikost/(8*sizeof(unsigned long)) + (velikost%(8*sizeof(unsigned long))?1:0)), sizeof(unsigned long)); \
                                            if (jmeno_pole == NULL) {error_exit("bitset_alloc: Chyba alokace paměti\n");} \
                                            *jmeno_pole = (velikost/(8*sizeof(unsigned long)) + (velikost%(8*sizeof(unsigned long))?1:0))*8*sizeof(unsigned long); \
                                            assert(*jmeno_pole <= velikost + CHAR_BIT*sizeof(unsigned long)-1);

#define bitset_free(jmeno_pole) free(jmeno_pole);

#ifndef USE_INLINE
    #define bitset_size(jmeno_pole) (unsigned long) (*jmeno_pole)

    #define bitset_setbit(jmeno_pole, index, vyraz) (index > *jmeno_pole-1)?(error_exit("bitset_setbit: Index %lu mimo rozsah 0..%lu\n", (unsigned long)index, (unsigned long)*jmeno_pole-1), 0):(vyraz?(jmeno_pole[index/(8*sizeof(unsigned long))] |= (1UL << (sizeof(unsigned long)*8-index%(sizeof(unsigned long)*8)))):(jmeno_pole[index/(8*sizeof(unsigned long))] &= (~(1UL << (sizeof(unsigned long)*8-index%(sizeof(unsigned long)*8))))))

    #define bitset_getbit(jmeno_pole, index) (index > *jmeno_pole-1)?(error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu\n", (unsigned long)index, (unsigned long)*jmeno_pole-1), 0):(((1UL << (sizeof(unsigned long)*8-index%(sizeof(unsigned long)*8)) & (jmeno_pole[index/(8*sizeof(unsigned long))])) > 0)?1:0)

#else
    static inline unsigned long bitset_size(bitset_t jmeno_pole) {
        return *jmeno_pole;
    }

    static inline void bitset_setbit(bitset_t jmeno_pole, bitset_index_t index, unsigned long vyraz) {
        if (index > *jmeno_pole-1) {
            error_exit("bitset_setbit: Index %lu mimo rozsah 0..%lu\n", (unsigned long)index, (unsigned long)*jmeno_pole-1);
        }
        vyraz?(jmeno_pole[index/(8*sizeof(unsigned long))] |= (1UL << (sizeof(unsigned long)*8-index%(sizeof(unsigned long)*8)))):(jmeno_pole[index/(8*sizeof(unsigned long))] &= (~(1UL << (sizeof(unsigned long)*8-index%(sizeof(unsigned long)*8)))));
        return;
    }

    static inline int bitset_getbit(bitset_t jmeno_pole, bitset_index_t index) {
        if (index > *jmeno_pole-1) {
            error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu\n", (unsigned long)index, (unsigned long)*jmeno_pole-1);
        }
        return ((1UL << (sizeof(unsigned long)*8-index%(sizeof(unsigned long)*8)) & (jmeno_pole[index/(8*sizeof(unsigned long))])) > 0)?1:0;
    }
    
#endif //end of USE_INLINE

#endif //end of BITSET_H
