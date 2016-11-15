#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
//#include "header.h"
#include "parser.h"

char word[13];
char number[13];
int tokenNum = 0;

void addToken(char *str, token_type tkn){
   strcpy(tokens[tokenNum].value, str);
   tokens[tokenNum++].type = tkn;
}

void lexer(FILE *pl0Code, FILE *codeFile, int comment_remove){

   char c;
   int flag = 0;
   char *ptr;

   fscanf(pl0Code, "%c", &c);
   while(c != EOF){
      // Deal with comments
      if (flag){
         if (comment_remove){
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
            fprintf(codeFile, "%c", c);
            c = fgetc(pl0Code);
            if (c == '*'){
               fprintf(codeFile, "%c", c);
               c = fgetc(pl0Code);
               if (c == '/'){
                  flag = 0;
                  fprintf(codeFile, "%c", c);
                  c = fgetc(pl0Code);
               }
            }
         }
      }

      // c is a space, tab, or newline
      else if ((int)c <= 32){
         fprintf(codeFile, "%c", c);
         c = fgetc(pl0Code);
      }

      // c is a non-numeric/non-alphabetic symbol
      else if (((int)c >= 40 && (int)c <= 47) || ((int)c >= 58 && (int)c <= 62)){
         if (c == '('){
            fprintf(codeFile, "%c", c);
            addToken("(", lparentsym);
            c = fgetc(pl0Code);
         }
         else if (c == ')'){
            fprintf(codeFile, "%c", c);
            addToken(")", rparentsym);
            c = fgetc(pl0Code);
         }
         else if (c == '*'){
            fprintf(codeFile, "%c", c);
            addToken("*", multsym);
            c = fgetc(pl0Code);
         }
         else if (c == '+'){
            fprintf(codeFile, "%c", c);
            addToken("+", plussym);
            c = fgetc(pl0Code);
         }
         else if (c == ','){
            fprintf(codeFile, "%c", c);
            addToken(",", commasym);
            c = fgetc(pl0Code);
         }
         else if (c == '-'){
            fprintf(codeFile, "%c", c);
            addToken("-", minussym);
            c = fgetc(pl0Code);
         }
         else if (c == '.'){
            fprintf(codeFile, "%c", c);
            addToken(".", periodsym);
            c = fgetc(pl0Code);
         }
         else if (c == '/'){
            c = fgetc(pl0Code);
            // We know it is a comment if * comes right after /
            if (c == '*'){
               if (!comment_remove)
                  fprintf(codeFile, "%c", '/');
               flag = 1;
            }
            else{
               fprintf(codeFile, "%c", c);
               addToken("/", slashsym);
            }
         }
         else if (c == ':'){
            fprintf(codeFile, "%c", c);
            c = fgetc(pl0Code);
            if (c == '='){
               fprintf(codeFile, "%c", c);
               addToken(":=", becomessym);
               c = fgetc(pl0Code);
            }
            else{
               printf("Error, : is not a valid token.");
               exit(0);
            }
         }
         else if (c == ';'){
            fprintf(codeFile, "%c", c);
            addToken(";", semicolonsym);
            c = fgetc(pl0Code);
         }
         else if (c == '<'){
            fprintf(codeFile, "%c", c);
            c = fgetc(pl0Code);
            if (c == '='){
               fprintf(codeFile, "%c", c);
               addToken("<=", leqsym);
               c = fgetc(pl0Code);
            }
            if (c == '>'){
               fprintf(codeFile, "%c", c);
               addToken("<>", neqsym);
               c = fgetc(pl0Code);
            }
            else{
               addToken("<", lessym);
               c = fgetc(pl0Code);
            }
         }
         else if (c == '='){
            fprintf(codeFile, "%c", c);
            addToken("=", eqsym);
            c = fgetc(pl0Code);
         }
         else if (c == '>'){
            fprintf(codeFile, "%c", c);
            c = fgetc(pl0Code);
            if (c == '='){
               fprintf(codeFile, "%c", c);
               addToken(">=", geqsym);
               c = fgetc(pl0Code);
            }
            else{
               addToken(">", gtrsym);
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
         if (strtol(number, &ptr, 10) > INT_MAX){
            printf("Error: number greater than INT_MAX\n");
            exit(0);
         }
         addToken(number, numbersym);
         fprintf(codeFile, "%s", number);
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
            addToken("const", constsym);
         }
         else if (strcmp(word, "var") == 0){
            addToken("var", varsym);
         }
         else if (strcmp(word, "procedure") == 0){
            addToken("procedure", procsym);
         }
         else if (strcmp(word, "call") == 0){
            addToken("call", callsym);
         }
         else if (strcmp(word, "begin") == 0){
            addToken("begin", beginsym);
         }
         else if (strcmp(word, "end") == 0){
            addToken("end", endsym);
         }
         else if (strcmp(word, "if") == 0){
            addToken("if", ifsym);
         }
         else if (strcmp(word, "then") == 0){
            addToken("then", thensym);
         }
         else if (strcmp(word, "else") == 0){
            addToken("else", elsesym);
         }
         else if (strcmp(word, "while") == 0){
            addToken("while", whilesym);
         }
         else if (strcmp(word, "do") == 0){
            addToken("do", dosym);
         }
         else if (strcmp(word, "read") == 0){
            addToken("read", readsym);
         }
         else if (strcmp(word, "write") == 0){
            addToken("write", writesym);
         }
         else if (strcmp(word, "odd") == 0){
            addToken("odd", oddsym);
         }
         else{
            addToken(word, identsym);
         }
         fprintf(codeFile, "%s", word);
      }
      else{
         printf("Error.");
         exit(0);
      }
   }
}

void printTable() {
    int i;
    printf("Tokens:\n-------\n");
    for(i = 0; i < tokenNum; i++) {
        printf("%s\t\t\t%d\n", tokens[i].value, tokens[i].type);
    }
}
