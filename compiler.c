// Compiler Builder 16
// Kenneth Mitchell
// Georg Anemogiannis
// David Israwi Yordi
// Tyler Chauhan


#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
    // Symbol Table
    #define MAX_SYMBOL_TABLE_SIZE 100
    typedef struct symbol {
        int kind; // const = 1, var = 2, proc = 3
        char name[12]; // name up to 11 chars
        int val; // number (ASCII value)
        int level; // L level
        int addr; // M address
    } symbol;
    symbol symbol_table[MAX_SYMBOL_TABLE_SIZE];

    return 0;
}
