/* Compiler Builder 16
   Kenneth Mitchell
   Georg Anemogiannis
   David Israwi Yordi
   Tyler Chauhan
*/

#include "header.h"

FILE* readf;
FILE* writef;



int main(int argc, char **argv)
{
	//reading
	argc--; argv++;
	readf = fopen(*argv, "rb");

	//writing
	argc--; argv++;
	writef = fopen(*argv, "wb");

	lexer(readf, fopen("LexerOutput", "wb"), 1);
}