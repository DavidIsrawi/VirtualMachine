#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Virtual Machine Constants
#define MAX_STACK_HEIGHT 2000
#define MAX_CODE_LENGTH 500
#define MAX_LEXI_LEVELS 3

//Parser Constants
#define MAX_SYMBOL_TABLE_SIZE 100

typedef struct symbol
{
  int kind; //const = 1, var = 2, proc = 3
  char name[12]; //name up to 11 characters
  int val; //number (ASCII value)
  int level; //L level
  int addr; //M address
} symbol;

typedef enum token{
  nulsym = 1, identsym, numbersym, plussym, minussym,
  multsym, slashsym, oddsym, eqsym, neqsym, lessym, leqsym,
  gtrsym, geqsym, lparentsym, rparentsym, commasym, semicolonsym,
  periodsym, becomessym, beginsym, endsym, ifsym, thensym,
  whilesym, dosym, callsym, constsym, varsym, procsym, writesym,
  readsym , elsesym
} token_type;

typedef struct {
   char value[13];
   token_type type;
} token;

token tokens[1000];


void lexer(FILE*, FILE*, int);
void program();
