// Compiler Builder 16
// Kenneth Mitchell
// Georg Anemogiannis
// David Israwi Yordi
// Tyler Chauhan

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int print (int op, int l, int m);
void term();

int nextToken;

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

void term() {
    factor();

    while(nextToken == multsym || nextToken == slashsym) {

        getNextToken();
        factor();

        // If mult - add mult to code
        if(nextToken == multsym) {
            print(2, 0, 4);
        }
        // If div - add div to code
        else {
            print(2, 0, 5);
        }
    }
}

int print (int op, int l, int m) {

}
