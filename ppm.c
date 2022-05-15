// ppm.c
// Řešení IJC-DU1, příklad b), 12.3.2022
// Autor: Martin Kubička, FIT
// Přeloženo: gcc 7.5

#include "ppm.h"
#include "error.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

struct ppm * ppm_read(const char * filename) {
    int xsize = 0, ysize = 0;
    //opening file
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        error_exit("Nepodarilo sa načítať súbor!\n");
    }
    
    //creating string with no size
    char *string = malloc(0*sizeof(char));
    if (string == NULL) {
        error_exit("Chyba alokácie!\n");
    }

    int c = fgetc(file);
    int count = 0;
    //counter for number of chars added
    int charCount = 1;
    while (c != EOF) {
        //if char is whitespace
        if (isspace(c)) {
            //getting format of picture
            if (count == 0) {
                if (!(strcmp(string, "P6"))) {
                    count++;
                } else {
                    warning_msg("Nie je zhodný s formátom P6\n");
                    return NULL;
                }
            //getting xsize of picture
            } else if (count == 1) {
                if (0 <= atoi(string) && atoi(string) <= 255) {
                    xsize = atoi(&string[0]);
                } else {
                    error_exit("Položka 1 nie je číslo!\n");
                }
                count++;
            //getting ysize of picture
            } else {
                if (0 <= atoi(string) && atoi(string) <= 255) {
                    ysize = atoi(&string[0]);
                } else {
                    error_exit("Položka 2 nie je číslo!\n");
                }
                free(string);
                c = fgetc(file);
                break;
            }
            //reseting values
            free(string);
            string = malloc(0*sizeof(char));
            if (string == NULL) {
                error_exit("Chyba alokácie!\n");
            }
            charCount = 1;
        } else {
            /* if char is not whitespace string will be reallocated and
               char will be added to string */ 
            string = realloc(string, (charCount+1)*sizeof(char));
            if (string == NULL) {
                error_exit("Chyba alokácie!\n");
            }
            string[charCount-1] = c;
            charCount++;
        }
        c = fgetc(file);
    }
    //skipping to image data
    count = 0;
    while (c != EOF) {
        if (!isspace(c)) {
            count++;
        } else if (count != 0) {
            while (isspace(c)) {
                c = fgetc(file);
            }
            break;
        }
        c = fgetc(file);
    }

    //creating wanted structure
    struct ppm *image = malloc(sizeof(struct ppm) + 3*xsize*ysize);
    if (image == NULL) {
        error_exit("Chyba alokácie!\n");
    }
    image->xsize = xsize;
    image->ysize = ysize;
    int begg = 0;
    count = 0;
    //adding image data to created structure
    while (c != EOF) {
        if (begg == 0) {
            if (!isspace(c)) {
                begg = 1;
            }
        }
        if (begg != 0) {
            image->data[count] = c;
        }
        count++;
        c = fgetc(file);
    }
    fclose(file);
    return image;
}

void ppm_free(struct ppm *p) {
    free(p);
}

