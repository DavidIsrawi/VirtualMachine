#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*PL0 Token Types*/
typedef enum token {
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

char word[13];
char number[13];
token tokens[1000];
int tokenNum = 0;

void lexer(FILE *pl0Code, int flag){

   char c;
   char d;

   fscanf(pl0Code, "%c", &c);
   while(c != EOF){
      // Remove comments
      if (flag == 1){
         if (c == '/' && (d = fgetc(pl0Code)) == '*'){
            //c = fgetc(pl0Code);
            while (fscanf(pl0Code, "%c", &c) != '*');
            c = fgetc(pl0Code);
         }
      }

      // c is a space, tab, or newline
      else if (c == ' ' || c == '\t' || c == '\n'){
         printf("%c", c);
         c = fgetc(pl0Code);
      }

      // c is a non-numeric/non-alphabetic symbol
      else if (((int)c >= 40 && (int)c <= 47) || ((int)c >= 58 && (int)c <= 62)){
         if (c == '('){
            printf("%c", c);
            strcpy(tokens[tokenNum].value, "(");
            tokens[tokenNum++].type = lparentsym;
            c = fgetc(pl0Code);
         }
         else if (c == ')'){
            printf("%c", c);
            strcpy(tokens[tokenNum].value, ")");
            tokens[tokenNum++].type = rparentsym;
            c = fgetc(pl0Code);
         }
         else if (c == '*'){
            printf("%c", c);
            strcpy(tokens[tokenNum].value, "*");
            tokens[tokenNum++].type = multsym;
            c = fgetc(pl0Code);
         }
         else if (c == '+'){
            printf("%c", c);
            strcpy(tokens[tokenNum].value, "+");
            tokens[tokenNum++].type = plussym;
            c = fgetc(pl0Code);
         }
         else if (c == ','){
            printf("%c", c);
            strcpy(tokens[tokenNum].value, ",");
            tokens[tokenNum++].type = commasym;
            c = fgetc(pl0Code);
         }
         else if (c == '-'){
            printf("%c", c);
            strcpy(tokens[tokenNum].value, "-");
            tokens[tokenNum++].type = minussym;
            c = fgetc(pl0Code);
         }
         else if (c == '.'){
            printf("%c", c);
            strcpy(tokens[tokenNum].value, ".");
            tokens[tokenNum++].type = periodsym;
            c = fgetc(pl0Code);
         }
         else if (c == '/'){
            printf("%c", c);
            strcpy(tokens[tokenNum].value, "/");
            tokens[tokenNum++].type = slashsym;
            c = fgetc(pl0Code);
         }
         else if (c == ':'){
            printf("%c", c);
            c = fgetc(pl0Code);
            if (c == '='){
               strcpy(tokens[tokenNum].value, ":=");
               tokens[tokenNum++].type = becomessym;
               c = fgetc(pl0Code);
            }
            else{
               printf("Error, : is not a valid token.");
               exit(0);
            }
         }
         else if (c == ';'){
            printf("%c", c);
            strcpy(tokens[tokenNum].value, ";");
            tokens[tokenNum++].type = semicolonsym;
            c = fgetc(pl0Code);
         }
         else if (c == '<'){
            printf("%c", c);
            c = fgetc(pl0Code);
            if (c == '='){
               printf("%c", c);
               strcpy(tokens[tokenNum].value, "<=");
               tokens[tokenNum++].type = leqsym;
               c = fgetc(pl0Code);
            }
            if (c == '>'){
               printf("%c", c);
               strcpy(tokens[tokenNum].value, "<>");
               tokens[tokenNum++].type = neqsym;
               c = fgetc(pl0Code);
            }
            else{
               strcpy(tokens[tokenNum].value, "<");
               tokens[tokenNum++].type = lessym;
               c = fgetc(pl0Code);
            }
         }
         else if (c == '='){
            printf("%c", c);
            strcpy(tokens[tokenNum].value, "=");
            tokens[tokenNum++].type = eqsym;
            c = fgetc(pl0Code);
         }
         else if (c == '>'){
            printf("%c", c);
            c = fgetc(pl0Code);
            if (c == '='){
               printf("%c", c);
               strcpy(tokens[tokenNum].value, ">=");
               tokens[tokenNum++].type = geqsym;
               c = fgetc(pl0Code);
            }
            else{
               strcpy(tokens[tokenNum].value, ">");
               tokens[tokenNum++].type = gtrsym;
               c = fgetc(pl0Code);
            }
         }
      }

      // c is a number
      else if ((int)c >= 48 && (int)c <= 57){
         number[0] = c;
      }
      // c is a lowercase letter
      else if ((int)c >= 97 && (int)c <= 122){
         int position = 0;

         while(((int)c >= 48 && (int)c <= 57) || ((int)c >= 97 && (int)c <= 122)){
            word[position++] = c;
            if (position >= 12){
               printf("Error: identifier longer than 12 characters\n");
               exit(0);
            }
            else
               c = fgetc(pl0Code);
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
