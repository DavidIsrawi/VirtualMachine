#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Virtual Machine*/
#define MAX_STACK_HEIGHT 2000
#define MAX_CODE_LENGTH 500
#define MAX_LEXI_LEVELS 3

//OP Codes
// first index is empty string to accomodate the opcode to its correct value
char* instCode[] = {
	"",
	"LIT",
	"OPR",
	"LOD",
	"STO",
	"CAL",
	"INC",
	"JMP",
	"JPC",
	"SIO"
};

//Operator Codes
char* OPRCode[] = {
	"RET",
	"NEG",
	"ADD",
	"SUB",
	"MUL",
	"DIV",
	"ODD",
	"MOD",
	"EQL",
	"NEQ",
	"LSS",
	"LEQ",
	"GTR",
	"GEQ"
};

//Instruction struct
typedef struct
{
	int op;
	int  l;
	int  m;
} instruction;
/*************************************/

/*Lexer*/
//Declare token types
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
/******************************************/

/*Parser*/
#define MAX_SYMBOL_TABLE_SIZE 100

typedef struct symbol
{
  int kind; //const = 1, var = 2, proc = 3
  char name[12]; //name up to 11 characters
  int val; //number (ASCII value)
  int level; //L level
  int addr; //M address
} symbol;
/***************************************************/


void lexer(FILE*, FILE*, int);
void program();
