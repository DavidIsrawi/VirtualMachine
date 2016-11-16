/* Compiler Builder 16
   Kenneth Mitchell
   Georg Anemogiannis
   David Israwi Yordi
   Tyler Chauhan
*/

#include "lexer.h"

int main(int argc, char *argv[])
{
   FILE *fo = fopen("input.pl0", "rb");
   FILE *wf = fopen("text.pm0", "w");
   lexer(fo, wf, 1);
   program();

   int x;
   for (x = 0; x < cx; x++)
   {
	   printf("%d %d %d\n", code[x].op, code[x].l, code[x].m);
   }

   fclose(fo);
   fclose(wf);
}
