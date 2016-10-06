#include <stdio.h>

/*PL0 Token Types*/
typedef enum token {
  nulsym = 1, identsym, numbersym, plussym, minussym,
  multsym, slashsym, oddsym, eqsym, neqsym, lessym, leqsym,
  gtrsym, geqsym, lparentsym, rparentsym, commasym, semicolonsym,
  periodsym, becomessym, beginsym, endsym, ifsym, thensym,
  whilesym, dosym, callsym, constsym, varsym, procsym, writesym,
  readsym , elsesym
} token_type;

union lval {
  char *id;
  int num;   // not recognized yet
} lval;

typedef struct {
   char value[13];
   token_type type;
} token;

FILE *pl0Code;
FILE *codeNoComments;
char word[13];
token tokens[1000];
int tokenNum = 0;



token_type lex() {
  char c;
  // ignore space, tab, newline
  while ((c=getchar()) == ' ' || c== '\t' || c == '\n')
    ;
  if (c == EOF) return nulsym;

  // identifier
  if (isalpha(c)) {
    char sbuf[100], *p = sbuf;
    do {
      *p++ = c;
    } while ((c=getchar()) != EOF && isalnum(c));
    ungetc(c, stdin);
    *p = '\0';
    lval.id = sbuf;
    return idsym;
  }

  switch (c) {
    case '+' :
      return plussym;
    case '*' :
      return multsym;
    case '(' :
      return lparensym;
    case ')' :
      return rparensym;
    default  :
      printf("illegal token\n");
  }
}

void removeComments(int flag){

   char c;
   char d;
   codeNoComments = fopen(fileCodeNoComments, "w");

   while(fscanf(pl0Code, "%c", &c) != EOF){
      // Remove comments
      if (flag == 1){
         if (c == '/' && (d = fgetc(pl0Code)) == '*'){
            c = fgetc(pl0Code);
            while (fscanf(pl0Code, "%c", &c) != '*');
            c = fgetc(pl0Code);
         }
      }

      // c is a number
      if ((int)c >= 48 && (int)c <= 57){

      }
      // c is a lowercase letter
      else if ((int)c >= 97 && (int)c <= 122){
         int position = 0;

         while(((int)c >= 48 && (int)c <= 57) || ((int)c >= 97 && (int)c <= 122)){
            word[position++] = c;
            if (position >= 12){
               printf("Error: identifier longer than 12 characters\n");
               break;
            }
            else
               c = fgetf(pl0Code);
         }

         word[position] = '\0';
         if (strcmp(word, "const") == 0){
            strcpy(tokens[tokenNum].value, "const");
            tokens[tokenNum++].type = constsym;
         }
         else if (strcmp(word, "var") == 0){
            strcpy(tokens[tokenNum].value, "var");
            tokens[tokenNum++].type = varsym;
         }
         else if (strcmp(word, "procedure") == 0){
            strcpy(tokens[tokenNum].value, "procedure");
            tokens[tokenNum++].type = procsym;
         }
         else if (strcmp(word, "call") == 0){
            strcpy(tokens[tokenNum].value, "call");
            tokens[tokenNum++].type = callsym;
         }
         else if (strcmp(word, "begin") == 0){
            strcpy(tokens[tokenNum].value, "begin");
            tokens[tokenNum++].type = beginsym;
         }
         else if (strcmp(word, "end") == 0){
            strcpy(tokens[tokenNum].value, "end");
            tokens[tokenNum++].type = endsym;
         }
         else if (strcmp(word, "if") == 0){
            strcpy(tokens[tokenNum].value, "if");
            tokens[tokenNum++].type = ifsym;
         }
         else if (strcmp(word, "then") == 0){
            strcpy(tokens[tokenNum].value, "then");
            tokens[tokenNum++].type = thensym;
         }
         else if (strcmp(word, "else") == 0){
            strcpy(tokens[tokenNum].value, "else");
            tokens[tokenNum++].type = elsesym;
         }
         else if (strcmp(word, "while") == 0){
            strcpy(tokens[tokenNum].value, "while");
            tokens[tokenNum++].type = whilesym;
         }
         else if (strcmp(word, "do") == 0){
            strcpy(tokens[tokenNum].value, "do");
            tokens[tokenNum++].type = dosym;
         }
         else if (strcmp(word, "read") == 0){
            strcpy(tokens[tokenNum].value, "read");
            tokens[tokenNum++].type = readsym;
         }
         else if (strcmp(word, "write") == 0){
            strcpy(tokens[tokenNum].value, "write");
            tokens[tokenNum++].type = writesym;
         }
         else if (strcmp(word, "odd") == 0){
            strcpy(tokens[tokenNum].value, "odd");
            tokens[tokenNum++].type = oddsym;
         }
         else{
            strcpy(tokens[tokenNum].value, word);
            tokens[tokenNum++].type = identsym;
         }
      }
   }
}

main() {
  printf("example lexer\n");
  token_type tok;
  while ((tok=lex()) != nulsym) {
    printf("token type: %d", tok);
    if (tok == idsym) printf(" semantic value: %s", lval.id);
    printf("\n");
  }
}
