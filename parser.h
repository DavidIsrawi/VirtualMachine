/* Compiler Builder 16
   Kenneth Mitchell
   Georg Anemogiannis
   David Israwi Yordi
   Tyler Chauhan
*/

#include "header.h"

/* Symbol table */
symbol symbol_table[MAX_SYMBOL_TABLE_SIZE];

/* Current Token */
token currentTok;
int tokenNumber = 0;

/* Functions */
void program();
void block();
void statement();
void condition();
void expression();
void term();
void factor();
void getToken();
void errorMessage(int x);


/* program ::= block "." */
void program()
{
  getToken(); //retrieve the token
  block(); //

  if(currentTok.type != periodsym)
  {
    errorMessage(9);
  }
}

/* block ::= const-declaration var-declaration statement */
void block()
{

   if (currentTok.type == constsym)
   {
      do {
         getToken();
         if (currentTok.type != identsym)
            errorMessage(25);
         getToken();
         if (currentTok.type != eqsym)
            errorMessage(25);
         getToken();
         if (currentTok.type != numbersym)
            errorMessage(25);
         getToken();
      } while(currentTok.type == commasym);

      if (currentTok.type != semicolonsym)
         errorMessage(25);
      getToken();
   }

   if (currentTok.type == varsym)
   {
      do {
         getToken();
         if (currentTok.type != identsym)
            errorMessage(25);
         getToken();
      } while(currentTok.type == commasym);

      if (currentTok.type != semicolonsym)
         errorMessage(25);
      getToken();
   }

   while (currentTok.type == procsym)
   {
      getToken();
      if (currentTok.type != identsym)
         errorMessage(25);
      getToken();
      if (currentTok.type != semicolonsym)
         errorMessage(25);
      getToken();
      block();
      if (currentTok.type != semicolonsym)
         errorMessage(25);
      getToken();
   }

   statement();
}

/* statement ::= [ ident “:=” expression
    | “begin” statement { “;” statement } “end”
    | “if” condition “then” statement ]
*/
void statement()
{
   if (currentTok.type == identsym)
   {
      getToken();
      if (currentTok.type != becomessym)
         errorMessage(25);
      getToken();
      expression();
   }
   else if (currentTok.type == callsym)
   {
      getToken();
      if (currentTok.type != identsym)
         errorMessage(25);
      getToken();
   }
   else if (currentTok.type == beginsym)
   {
      getToken();
      statement();
      while (currentTok.type == semicolonsym)
      {
         getToken();
         statement();
      }
      if (currentTok.type != endsym)
         errorMessage(25);
      getToken();
   }
   else if (currentTok.type == ifsym)
   {
      getToken();
      condition();
      if (currentTok.type != thensym)
         errorMessage(25);
      getToken();
      statement();
   }
   else if (currentTok.type == whilesym)
   {
      getToken();
      condition();
      if (currentTok.type != dosym)
         errorMessage(25);
      getToken();
      statement();
   }
}

/*condition ::= “odd” expression
    | expression rel-op expression */
void condition()
{
   if (currentTok.type == oddsym)
   {
      getToken();
      expression();
   }
   else
   {
      expression();
      if (currentTok.type != leqsym || currentTok.type != neqsym || currentTok.type != lessym || currentTok.type != geqsym || currentTok.type != gtrsym || currentTok.type != eqsym)
         errorMessage(25);
      getToken();
      expression();
   }
}

/* expression ::= [ “+” | “-” ] term { ( “+” | “-” ) term} */
void expression()
{
   if (currentTok.type == plussym || currentTok.type == minussym)
      getToken();
   term();
   while (currentTok.type == plussym || currentTok.type == minussym)
   {
      getToken();
      term();
   }
}

/* term ::= factor { ( “*” | “/” ) factor } */
void term()
{
    factor();
    while(currentTok.type == multsym || currentTok.type == slashsym) {
        getToken();
        factor();
        /*
        // If mult - add mult to code
        if(currentTok.type == multsym) {
            print(2, 0, 4);
        }
        // If div - add div to code
        else {
            print(2, 0, 5);
        }
        */
    }
}

/* factor ::= ident | number | “(” expression “)”*/
void factor()
{
   if (currentTok.type == identsym)
      getToken();
   else if (currentTok.type == numbersym)
      getToken();
   else if (currentTok.type == lparentsym)
   {
      getToken();
      expression();
      if (currentTok.type != rparentsym)
         errorMessage(25);
      getToken();
   }
   else
      errorMessage(25);
}

/* function to get the current token */
void getToken()
{
  currentTok = tokens[tokenNumber++];
}

/* Error messages for the tiny PL/0 Parser */
void errorMessage(int x)
{
  /*if(x != 0)
  {
    printf("Error number %d:  ", x);
  }
  */

  switch(x)
  {
    case 0:
      printf("No errors, program is syntactically correct.\n");
      break;
    case 1:
      printf("Use = instead of :=.\n");
      break;
    case 2:
      printf("= must be followed by a number.\n");
      break;
    case 3:
      printf("Identifier must be followed by a =.\n");
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
