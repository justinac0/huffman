#ifndef _SYMBOLS_H_
#define _SYMBOLS_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

typedef struct {
    uint32_t* occurence;
} Symbols;

Symbols
symbols_create(const char* data, size_t data_size) {
    Symbols symbols;
    symbols.occurence = (uint32_t*) calloc(sizeof(uint32_t), UINT8_MAX);

    if (!symbols.occurence) {
        fprintf(stderr, "failed to allocate memory!\n");
    }

    for (int i = 0; i < data_size; i++) {
        symbols.occurence[data[i]]++;
    }

    return symbols;
}

void
symbols_destroy(Symbols* sym) {
    free(sym->occurence);
    sym->occurence = NULL;
}

#endif // _SYMBOLS_H_
