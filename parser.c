// Compiler Builder 16
// Kenneth Mitchell
// Georg Anemogiannis
// David Israwi Yordi
// Tyler Chauhan

#include "header.h"

//Symbol table
symbol symbol_table[MAX_SYMBOL_TABLE_SIZE];
token_type curToken;

//Functions
void program();
void block();
void statement();
void condition();
void expression();
void term();
void factor();
void errorMessage(int x);




//<program> ::= block "."
void program()
{



}

//Error messages for the tiny PL/0 Parser
void errorMessage(int x)
{
  switch(x)
  {
    case 1:
      printf("Use = instead of :=.\n");
      break;
    case 2:
      printf("= must be followed by a number.\n");
      break;
    case 3:
      print("Identifier must be followed by a =.\n");
      break;
    case 4:
      printf("const, var, procedure must be followed by identifier.\n");
      break;
    case 5:
      printf("Semicolon or comma missing.\n");
      break;
    case 6:
      printf("Incorrect symbol after procedure declaration.\n");
      break;
    case 7:
      printf("Statement expected.\n");
      break;
    case 8:
      printf("Incorrect symbol after statement part in block.\n");
      break;
    case 9:
      printf("Period expected.\n");
      break;
    case 10:
      printf("Semicolon between statements missing.\n");
      break;
    case 11:
      printf("Undeclared identifier.\n");
      break;
    case 12:
      printf("Assignment to constant or procedure is not allowed.\n");
      break;
    case 13:
      printf("Assignment operator expected.\n");
      break;
    case 14:
      printf("call must be followed by an identifier.\n");
      break;
    case 15:
      printf("Call of a constant or variable is meaningless\n");
      break;
    case 16:
      printf("then expected.\n");
      break;
    case 17:
      printf("Semicolon or } expected.\n");
      break;
    case 18:
      printf("do expected.\n");
      break;
    case 19:
      printf("Incorrect symbol following statement.\n");
      break;
    case 20:
      printf("Relational operator expected.\n");
      break;
    case 21:
      printf("Expression must not contain a procedure identifier.\n");
      break;
    case 22:
      printf("Right parenthesis missing.\n");
      break;
    case 23:
      printf("The preceding factor cannot begin with this symbol\n");
      break;
    case 24:
      printf("An expression cannot begin with this symbol.\n");
      break;
    case 25:
      printf("This number is too large.\n");
      break;
    default:
      printf("Error. There was a problem with the code.\n");
  }
  exit(x);
}
