#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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

void lexer(FILE *pl0Code, int commentRemove){

   char c;
   int flag = 0;

   fscanf(pl0Code, "%c", &c);
   while(c != EOF){
      // Deal with comments
      if (flag){
         if (commentRemove){
            c = fgetc(pl0Code);
            if (c == '*'){
               c = fgetc(pl0Code);
               if (c == '/'){
                  flag = 0;
                  c = fgetc(pl0Code);
               }
            }
         }
         else{
            printf("%c", c);
            c = fgetc(pl0Code);
            if (c == '*'){
               printf("%c", c);
               c = fgetc(pl0Code);
               if (c == '/'){
                  flag = 0;
                  printf("%c", c);
                  c = fgetc(pl0Code);
               }
            }
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
            c = fgetc(pl0Code);
            // We know it is a comment if * comes right after /
            if (c == '*'){
               flag = 1;
            }
            else{
               printf("%c", c);
               strcpy(tokens[tokenNum].value, "/");
               tokens[tokenNum++].type = slashsym;
            }
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
      else if (isdigit(c)){
         int position = 0;

         while(isdigit(c)){
            number[position++] = c;
            if (position >= 12){
               printf("Error: number longer than 12 characters\n");
               exit(0);
            }
            else
               c = fgetc(pl0Code);
         }

         if (isalpha(c)){
            printf("Error: invalid identifier\n");
            exit(0);
         }

         number[position] = '\0';
         strcpy(tokens[tokenNum].value, number);
         tokens[tokenNum++].type = numbersym;
         printf("%s", number);
      }
      // c is a lowercase letter
      else if (isalpha(c)){
         int position = 0;

         while(isdigit(c) || isalpha(c)){
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

// Could use this functions if we want to, I just thought of it now
/*
void addToken(char *str, token_type tkn){
   strcpy(tokens[tokenNum].value, str);
   tokens[tokenNum++].type = tkn;
}
*/
