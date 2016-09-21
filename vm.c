// Compiler Builder 16
// Tyler Chauhan

#include <stdlib.h>
#include <stdio.h>

#define MAX_STACK_HEIGHT = 2000;
#define MAX_CODE_LENGTH = 500;
#define MAX_LEXI_LEVELS = 3;

typedef struct {
int op;
int  l;
int  m;
} instruction;

// Registers
int sp = 0;
int bp = 1;
int pc = 0;
instruction ir;

int stack[MAX_STACK_HEIGHT];
instruction code[MAX_CODE_LENGTH];
int code_length = 0;

void readPM0()
{
	FILE *fp = fopen("mcode.pm0", "r")
	int op, l, m, i = 0;
	while(fscanf(fp, "%d", op) != EOF)
	{
		fscanf(fp, "%d", l);
		fscanf(fp, "%d", m);
		
		code[i].op = op;
		code[i].l = l;
		code[i].m = m;
		i++;
	}
	
	code_length = i;
}

void printCode()
{
	int i;
	
	printf("PL/0 code:\n\n");
	for (i = 0; i < code_length; i++)
		printf("%d %d %d %d\n", i, code[i].op, code[i].l, code[i].m);
}

void fetchCycle()
{
	ir = code[pc];
	pc++;
}