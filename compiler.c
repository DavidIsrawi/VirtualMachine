/* Compiler Builder 16
   Kenneth Mitchell
   Georg Anemogiannis
   David Israwi Yordi
   Tyler Chauhan
*/

#include "lexer.h"

int main(int argc, char *argv[])
{
   if(argc != 3){
      printf("Error\n");
   }
   else
   {
      FILE *fo = fopen(argv[1], "rb");
      FILE *output = fopen(argv[2], "w");

      FILE *cleanCode = fopen("cleanCode.pl0", "w");
      lexer(fo, cleanCode, 1);
      program();
      writeToFile(output);

      fclose(fo);
      fclose(cleanCode);
      fclose(output);
   }
}
