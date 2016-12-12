/* Compiler Builder 16
   Kenneth Mitchell
   Georg Anemogiannis
   David Israwi Yordi
   Tyler Chauhan
*/

#include "header.h"

/* Symbol table */
symbol symbol_table[MAX_SYMBOL_TABLE_SIZE];
instruction code[MAX_CODE_LENGTH];

int symTableLoc = 0;

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
void emit(int op, int l, int m);
symbol * get_symbol(char *name);
void put_symbol(int kind, char* name, int val, int level, int addr);


int cx = 0;
int level = 0;

/* program ::= block "." */
void program()
{
  getToken(); //retrieve the token
  block(); //

  if(currentTok.type != periodsym)
  {
    errorMessage(9);
  }

  //halt command
  emit(9, 0, 2);
}

/* block ::= const-declaration var-declaration statement */
void block()
{
   int ctemp = cx;
   int num_vars = 0;
   emit(7, 0, 0);
   if (currentTok.type == constsym)
   {
	  char id[13];

      do {
		  //setting constant name
         getToken();
         if (currentTok.type != identsym)
            errorMessage(4);
		 strcpy(id, currentTok.value);

		 //checking if it has an equal sign
         getToken();
         if (currentTok.type == becomessym)
            errorMessage(1);
         if (currentTok.type != eqsym)
            errorMessage(3);

		 //get value
         getToken();
         if (currentTok.type != numbersym)
            errorMessage(2);

		 //create symbol
		 put_symbol(1, id, atoi(currentTok.value), level, 0);

         getToken();
      } while(currentTok.type == commasym);

      if (currentTok.type != semicolonsym)
         errorMessage(5);
      getToken();
   }

   if (currentTok.type == varsym)
   {
      num_vars = 0;
      do {
         getToken();
         if (currentTok.type != identsym)
            errorMessage(4);

		 //adding variable
		 num_vars++;
		 put_symbol(2, currentTok.value, 0, level, 3 + num_vars);

         getToken();
      } while(currentTok.type == commasym);

      if (currentTok.type != semicolonsym)
         errorMessage(5);
      getToken();

   }

   while (currentTok.type == procsym)
   {
      getToken();
      if (currentTok.type != identsym)
         errorMessage(4);

      put_symbol(3, currentTok.value, 0, level, cx);
      level++;

      getToken();
      if (currentTok.type != semicolonsym)
         errorMessage(5);
      getToken();
      block();
      emit(2, 0, 0);
      //code[temp].m = cx;
      level--;
      if (currentTok.type != semicolonsym)
         errorMessage(55);
      getToken();
   }
   code[ctemp].m = cx;

   //INC = instCode[6]
   emit(6, 0, 4 + num_vars);

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
      symbol* sym = get_symbol(currentTok.value);

      getToken();
      if (currentTok.type != becomessym)
         errorMessage(13);
      getToken();
      expression();

	  emit(4, level - sym->level, sym->addr);
   }
   else if (currentTok.type == callsym)
   {
      getToken();
      if (currentTok.type != identsym)
         errorMessage(14);
      symbol* sym = get_symbol(currentTok.value);
      emit(5, level - sym->level, sym->addr);
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
         errorMessage(8);
      getToken();
   }
   else if (currentTok.type == ifsym)
   {
      getToken();
      condition();
      if (currentTok.type != thensym)
         errorMessage(16);
      getToken();

	  int ctemp = cx;
	  emit(8, 0, 0);
      statement();

	  code[ctemp].m = cx;

      if (currentTok.type == elsesym) {
         code[ctemp].m = cx + 1;

         ctemp = cx;
         emit(7, 0, 0);
         getToken();
         statement();

         code[ctemp].m = cx;
      }
   }
   else if (currentTok.type == whilesym)
   {
      int cx1, cx2;

      cx1 = cx;
      getToken();
      condition();
      cx2 = cx;
      emit(8, 0, 0);
      if (currentTok.type != dosym)
         errorMessage(18);
      getToken();
      statement();
      int cxtemp = cx;
      emit(7, 0, cx1);
      code[cx2].m = cx;
   }
   else if (currentTok.type == readsym)
   {
	   getToken();
	   if (currentTok.type != identsym)
		   errorMessage(14);
	   symbol* sym = get_symbol(currentTok.value);

	   //read input
	   emit(9, 0, 1);

	   if (currentTok.type == identsym)
		   emit(4, 0, sym->addr);
	   else
		   emit(1, 0, atoi(currentTok.value));

	   getToken();
   }
   else if (currentTok.type == writesym)
   {
	   getToken();
	   if (currentTok.type != identsym && currentTok.type != numbersym)
		   errorMessage(14);

	   symbol* sym = get_symbol(currentTok.value);

	   if (sym->kind == 2)
		   emit(3, level - sym->level, sym->addr);
	   else
		   emit(1, 0, sym->val);

	   //write output
	   emit(9, 0, 0);

	   getToken();
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
      if (currentTok.type != leqsym && currentTok.type != neqsym && currentTok.type != lessym && currentTok.type != geqsym && currentTok.type != gtrsym && currentTok.type != eqsym)
         errorMessage(20);

	  token curr = currentTok;

      getToken();
      expression();


	  switch (curr.type)
	  {
	  case leqsym: emit(2, 0, 11);
		  break;
	  case neqsym: emit(2, 0, 9);
		  break;
	  case lessym: emit(2, 0, 10);
		  break;
	  case geqsym: emit(2, 0, 13);
		  break;
	  case gtrsym: emit(2, 0, 12);
		  break;
	  case eqsym: emit(2, 0, 8);
		  break;
	  default: errorMessage(26);
	  }
   }
}

/* expression ::= [ “+” | “-” ] term { ( “+” | “-” ) term} */
void expression()
{
	int addop;
	if (currentTok.type == plussym || currentTok.type == minussym)
	{
		addop = currentTok.type;
		getToken();
		term();

		if (addop == minussym)
			emit(2, 0, 1);
	}
	else
		term();

	while (currentTok.type == plussym || currentTok.type == minussym)
	{
		addop = currentTok.type;
		getToken();
		term();

		if (addop == plussym)
			emit(2, 0, 2);
		else
			emit(2, 0, 3);
	}
}

/* term ::= factor { ( “*” | “/” ) factor } */
void term()
{
	int mulop;

    factor();
    while(currentTok.type == multsym || currentTok.type == slashsym) {
		mulop = currentTok.type;
        getToken();
        factor();

		if (mulop == multsym)
			emit(2, 0, 4);
		else
			emit(2, 0, 5);
    }
}

/* factor ::= ident | number | “(” expression “)”*/
void factor()
{
	if (currentTok.type == identsym)
	{
		symbol* sym = get_symbol(currentTok.value);
      if (sym->kind == 1)
         emit(1, 0, sym->val);
      else
		 emit(3, level - sym->level, sym->addr);

		getToken();
	}
	else if (currentTok.type == numbersym)
	{
		emit(1, 0, atoi(currentTok.value));

		getToken();
	}
	else if (currentTok.type == lparentsym)
   {
      getToken();
      expression();
      if (currentTok.type != rparentsym)
         errorMessage(22);
      getToken();
   }
   else
      errorMessage(23);
}

/* function to get the current token */
void getToken()
{
  currentTok = tokens[tokenNumber++];
}

/* Error messages for the tiny PL/0 Parser */
void errorMessage(int x)
{
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

void emit(int op, int l, int m)
{
  if(cx > MAX_CODE_LENGTH)
  {
    errorMessage(25);
  }
  else
  {
    code[cx].op = op;
    code[cx].l = l;
    code[cx].m = m;
    cx++;

	//printf("%d %d %d %d\n", op, l, m, cx);
  }
}

symbol* get_symbol(char *name)
{
  int i;
  for(i = symTableLoc - 1; i >= 0; i--)
  {
    if(strcmp(name, symbol_table[i].name) == 0)
    {
      return &symbol_table[i];
    }
  }
  return NULL;
}

void put_symbol(int kind, char* name, int val, int level, int addr)
{
  symbol_table[symTableLoc].kind = kind;
  strcpy(symbol_table[symTableLoc].name, name);
  symbol_table[symTableLoc].val = val;
  symbol_table[symTableLoc].level = level;
  symbol_table[symTableLoc].addr = addr;

  symTableLoc++;
}

void writeToFile(FILE *output)
{
   int i;
   for (i = 0; i < cx; i++)
      fprintf(output, "%d %d %d\n", code[i].op, code[i].l, code[i].m);
}
