#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*PL0 Token Types*/
typedef enum token
{
	nulsym = 1, identsym, numbersym, plussym, minussym,
	multsym, slashsym, oddsym, eqsym, neqsym, lessym, leqsym,
	gtrsym, geqsym, lparentsym, rparentsym, commasym, semicolonsym,
	periodsym, becomessym, beginsym, endsym, ifsym, thensym,
	whilesym, dosym, callsym, constsym, varsym, procsym, writesym,
	readsym, elsesym
} token_type;

typedef struct
{
	char value[13];
	token_type type;
} token;

char word[13];
char number[13];
token tokens[1000];
int tokenNum = 0;

void addToken(char *str, token_type tkn)
{
	strcpy(tokens[tokenNum].value, str);
	tokens[tokenNum++].type = tkn;
}

/*
void lexer(FILE *pl0Code, int comment_remove){

char c;
int flag = 0;

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
addToken("(", lparentsym);
c = fgetc(pl0Code);
}
else if (c == ')'){
printf("%c", c);
addToken(")", rparentsym);
c = fgetc(pl0Code);
}
else if (c == '*'){
printf("%c", c);
addToken("*", multsym);
c = fgetc(pl0Code);
}
else if (c == '+'){
printf("%c", c);
addToken("+", plussym);
c = fgetc(pl0Code);
}
else if (c == ','){
printf("%c", c);
addToken(",", commasym);
c = fgetc(pl0Code);
}
else if (c == '-'){
printf("%c", c);
addToken("-", minussym);
c = fgetc(pl0Code);
}
else if (c == '.'){
printf("%c", c);
addToken(".", periodsym);
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
addToken("/", slashsym);
}
}
else if (c == ':'){
printf("%c", c);
c = fgetc(pl0Code);
if (c == '='){
addToken(":=", becomessym);
c = fgetc(pl0Code);
}
else{
printf("Error, : is not a valid token.");
exit(0);
}
}
else if (c == ';'){
printf("%c", c);
addToken(";", semicolonsym);
c = fgetc(pl0Code);
}
else if (c == '<'){
printf("%c", c);
c = fgetc(pl0Code);
if (c == '='){
printf("%c", c);
addToken("<=", leqsym);
c = fgetc(pl0Code);
}
if (c == '>'){
printf("%c", c);
addToken("<>", neqsym);
c = fgetc(pl0Code);
}
else{
addToken("<", lessym);
c = fgetc(pl0Code);
}
}
else if (c == '='){
printf("%c", c);
addToken("=", eqsym);
c = fgetc(pl0Code);
}
else if (c == '>'){
printf("%c", c);
c = fgetc(pl0Code);
if (c == '='){
printf("%c", c);
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
addToken(number, numbersym);
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
}
}
}

void main(int argc, char **argv)
{
argc--; argv++;
char* foo = *argv;
FILE* fo = fopen(foo, "rb");

lexer(fo, 1);
}*/


//if 1, printing comments, print a space otherwise
int printingComments = 0;

int proccessTokens(char word[13])
{
	if (strcmp(word, "") == 0)
		return;

	if (strcmp(word, "const") == 0)
	{
		addToken("const", constsym);
	}
	else if (strcmp(word, "var") == 0)
	{
		addToken("var", varsym);
	}
	else if (strcmp(word, "procedure") == 0)
	{
		addToken("procedure", procsym);
	}
	else if (strcmp(word, "call") == 0)
	{
		addToken("call", callsym);
	}
	else if (strcmp(word, "begin") == 0)
	{
		addToken("begin", beginsym);
	}
	else if (strcmp(word, "end") == 0)
	{
		addToken("end", endsym);
	}
	else if (strcmp(word, "if") == 0)
	{
		addToken("if", ifsym);
	}
	else if (strcmp(word, "then") == 0)
	{
		addToken("then", thensym);
	}
	else if (strcmp(word, "else") == 0)
	{
		addToken("else", elsesym);
	}
	else if (strcmp(word, "while") == 0)
	{
		addToken("while", whilesym);
	}
	else if (strcmp(word, "do") == 0)
	{
		addToken("do", dosym);
	}
	else if (strcmp(word, "read") == 0)
	{
		addToken("read", readsym);
	}
	else if (strcmp(word, "write") == 0)
	{
		addToken("write", writesym);
	}
	else if (strcmp(word, "odd") == 0)
	{
		addToken("odd", oddsym);
	}
	else
	{
		addToken(word, identsym);
	}
}

int isRecognizedCommand(char c)
{
	if (c == '+' || c == '-' || c == '/' || c == '*' || c == '=' || c == ':' || c == '<' || c == '>' || c == '(' || c == ')' || c == ';' || c == ',' || c == '.')
		return 1;
	else
		return 0;
}

int CommentProccess(char inputfile[99999], int size, int currentPos)
{
	//if the current character and proceeding character are /*
	if (currentPos < size - 1 && inputfile[currentPos] == '/' && inputfile[currentPos + 1] == '*')
	{
		while (currentPos > 0 && !(inputfile[currentPos] == '/' && inputfile[currentPos - 1] == '*'))
		{

			if (printingComments)
				printf("%c", inputfile[currentPos]);
			else
				printf(" ");

			currentPos++;
		}
		currentPos++;
	}

	//if the current and proceeding character are //
	if (currentPos < size - 1 && inputfile[currentPos] == '/' && inputfile[currentPos + 1] == '/')
	{
		//wait until the end of the line
		while (currentPos < size && inputfile[currentPos] != '\n')
		{

			if (printingComments)
				printf("%c", inputfile[currentPos]);
			else
				printf(" ");

			currentPos++;
		}
		currentPos++;
	}

	return currentPos;
}

//procces a word chunk
void ProccessChunk(char word[13])
{
	if (word[0] != NULL)
		proccessTokens(word);
}

//reset a word to NULL
void ResetWord(char word[13])
{
	for (int x = 0; x < 13; x++)
	{
		word[x] = NULL;
	}
}

void proccessInputFile(char inputfile[99999], int size)
{
	char word[13];
	ResetWord(word);
	int wordCount = 0;
	for (int x = 0; x < size; x++)
	{
		//deal with comments
		x = CommentProccess(inputfile, size, x);

		//deal with a chunk
		if (isspace(inputfile[x]))
		{
			//procces current word and reset it
			ProccessChunk(word);
			ResetWord(word);
			wordCount = 0;
		}
		//deal with a chunk before an operator
		else if (isRecognizedCommand(inputfile[x]))
		{
			//procces current word and reset it
			ProccessChunk(word);
			ResetWord(word);
			wordCount = 0;

			//special case for parenthases
			if (inputfile[x] == '(')
			{
				//add character to current word
				word[wordCount] = inputfile[x];
				wordCount++;

				//procces current word and reset it
				ProccessChunk(word);
				ResetWord(word);
				wordCount = 0;

				continue;
			}

			//if it is a multicharacter command
			while (x < size && isRecognizedCommand(inputfile[x]))
			{
				//add character to current word
				word[wordCount] = inputfile[x];
				wordCount++;

				x++;
			}
			x--;

			//procces current word and reset it
			ProccessChunk(word);
			ResetWord(word);
			wordCount = 0;
		}
		else if (isalnum(inputfile[x]))
		{
			//input token is too large
			if (wordCount >= 13)
			{
				printf("Token Too Large");
			}

			//add character to current word
			word[wordCount] = inputfile[x];
			wordCount++;
		}
		else
		{
			printf("Invalid Token: %c", inputfile[x]);
			exit(0);
		}

		printf("%c", inputfile[x]);
	}
}

char inputfile[99999];
void lexerV2(FILE* file, int withComments)
{
	char character;

	int inputfilepointer = 0;
	while ((character = fgetc(file)) != EOF)
	{
		inputfile[inputfilepointer] = character;
		inputfilepointer++;
	}

	proccessInputFile(inputfile, inputfilepointer);
}

void main(int argc, char **argv)
{
	argc--; argv++;
	char* foo = *argv;
	FILE* fo = fopen(foo, "rb");

	lexerV2(fo, 1);

	/*
	for (int x = 0; x < tokenNum; x++)
	{
	printf("\n%d", tokens[x].type);
	}*/
}