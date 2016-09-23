// Compiler Builder 16
// Kenneth Mitchell
// Georg Anemogiannis
// David Israwi Yordi
// Tyler Chauhan


#include <stdlib.h>
#include <stdio.h>

#define MAX_STACK_HEIGHT 2000
#define MAX_CODE_LENGTH 500
#define MAX_LEXI_LEVELS 3

// Instruction struct
typedef struct
{
	int op;
	int  l;
	int  m;
} instruction;

// Registers
int sp = 0;
int bp = 1;
int pc = 0;
instruction ir;

// Instruction Code
// first index is empty string to accomodate the opcode to its correct value
char* instCode[] = {
	"",
	"LIT",
	"OPR",
	"LOD",
	"STO",
	"CAL",
	"INC",
	"JMP",
	"JPC",
	"SIO"
};

char* OPRCode[] = {
	"RET",
	"NEG",
	"ADD",
	"SUB",
	"MUL",
	"DIV",
	"ODD",
	"MOD",
	"EQL",
	"NEQ",
	"LSS",
	"LEQ",
	"GTR",
	"GEQ"
};

char* SIOCode[] = {
	"OUT",
	"INP",
	"HLT",
};

// Initial stack values
int stack[MAX_STACK_HEIGHT] = { 0, 0, 0 };
instruction code[MAX_CODE_LENGTH];
int code_length = 0;

// Function declarations
void LIT();
void OPR();
void LOD();
void STO();
void CAL();
void INC();
void JMP();
void JPC();
void SIO();
int base(int level, int b);
void readPM0(FILE *fp);
void printCode();
void fetchCycle();
void executeCycle();
void runPM0();

//Computes the base of AR L levels down
int base(int level, int b)
{
	while (level > 0)
	{
		b = stack[b + 1];
		level--;
	}

	return b;
}

void readPM0(FILE *fp)
{
	int op, l, m, i = 0;
	while (fscanf(fp, "%d", &op) != EOF)
	{
		fscanf(fp, "%d", &l);
		fscanf(fp, "%d", &m);

		// Update values
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
	{
		if (code[i].op == 4 || code[i].op == 5)
			printf("%d\t%s\t%d\t%d", i, instCode[code[i].op], code[i].l, code[i].m);
		else if (code[i].op == 9)
			printf("%d\t%s\t \t ", i, SIOCode[code[i].m]);
		else if (code[i].op == 2)
			if (code[i].m != 0)
				printf("%d\t%s\t \t%d", i, OPRCode[code[i].m], code[i].m);
			else
				printf("%d\t%s\t \t ", i, OPRCode[code[i].m]);
		else
			printf("%d\t%s\t \t%d", i, instCode[code[i].op], code[i].m);

		printf("\n");
	}

	printf("\n");
}

void runPM0()
{
	printf("Execution:\n");
	printf("\t\t\t\tpc\tbp\tsp\tstack\n");
	printf("\t\t\t\t %d\t %d\t %d\n", pc, bp, sp);
	while (code_length > 0)
	{
		if (code[pc].op == 4 || code[pc].op == 5)
			printf("%d\t%s\t%d\t%d", pc, instCode[code[pc].op], code[pc].l, code[pc].m);
		else if(code[pc].op == 9)
			printf("%d\t%s\t \t ", pc, SIOCode[code[pc].m]);
		else if (code[pc].op == 2)
			if(code[pc].m != 0)
				printf("%d\t%s\t \t%d", pc, OPRCode[code[pc].m], code[pc].m);
			else
				printf("%d\t%s\t \t ", pc, OPRCode[code[pc].m]);
		else
			printf("%d\t%s\t \t%d", pc, instCode[code[pc].op], code[pc].m);

		fetchCycle();
		executeCycle();
		printf("\t%d\t %d\t %d", pc, bp, sp);
		printf("\t");

		//print stack
		int x;
		for (x = 1; x <= sp; x++)
		{
			if (x == 7 && sp > 7)
				printf("| ");
			printf("%d ", stack[x]);
		}
		printf("\n");

		code_length--;
	}
}

void fetchCycle()
{
	ir = code[pc];
	pc++;
}

void executeCycle()
{
	switch (ir.op)
	{
	case 1: LIT();
		break;
	case 2: OPR();
		break;
	case 3: LOD();
		break;
	case 4: STO();
		break;
	case 5: CAL();
		break;
	case 6: INC();
		break;
	case 7: JMP();
		break;
	case 8: JPC();
		break;
	case 9: SIO();
		break;
	}
}

//Function Implementations
void LIT()
{
	sp++;
	stack[sp] = ir.m;
}
void OPR()
{
	switch (ir.m)
	{
	case 0: //RET
		sp = bp - 1;
		pc = stack[sp + 4];
		bp = stack[sp + 3];
		break;
	case 1: //NEG
		stack[sp] = -stack[sp];
		break;
	case 2: //ADD
		sp--;
		stack[sp] = stack[sp] + stack[sp + 1];
		break;
	case 3: //SUB
		sp--;
		stack[sp] = stack[sp] - stack[sp + 1];
		break;
	case 4: //MUL
		sp--;
		stack[sp] = stack[sp] * stack[sp + 1];
		break;
	case 5: //DIV
		sp--;
		stack[sp] = stack[sp] / stack[sp + 1];
		break;
	case 6: //ODD
		stack[sp] = stack[sp] % 2;
		break;
	case 7: //MOD
		sp--;
		stack[sp] = stack[sp] % stack[sp + 1];
		break;
	case 8: //EQL
		sp--;
		stack[sp] = stack[sp] == stack[sp + 1];
		break;
	case 9: //NEQ
		sp--;
		stack[sp] = stack[sp] != stack[sp + 1];
		break;
	case 10: //LSS
		sp--;
		stack[sp] = stack[sp] <  stack[sp + 1];
		break;
	case 11: //LEQ
		sp--;
		stack[sp] = stack[sp] <= stack[sp + 1];
		break;
	case 12: //GTR
		sp--;
		stack[sp] = stack[sp] >  stack[sp + 1];
		break;
	case 13: //GEQ
		sp--;
		stack[sp] = stack[sp] >= stack[sp + 1];
		break;
	}

}
void LOD()
{
	sp++;
	stack[sp] = stack[base(ir.l, bp) + ir.m];
}
void STO()
{
	stack[base(ir.l, bp) + ir.m] = stack[sp];
	sp--;
}
void CAL()
{
	stack[sp + 1] = 0;
	stack[sp + 2] = base(ir.l, bp);
	stack[sp + 3] = bp;
	stack[sp + 4] = pc;
	bp = sp + 1;
	pc = ir.m;
}
void INC()
{
	sp += ir.m;
}
void JMP()
{
	pc = ir.m;
}
void JPC()
{
	if (stack[sp] == 0)
	{
		pc = ir.m;
	}
	sp--;
}
void SIO()
{
	int input;
	switch (ir.m)
	{
	case 0:
		printf("%d", stack[sp]);
		sp--;
		break;
	case 1: //input value
		sp++;
		printf("Enter a value to push onto the stack: ");
		scanf("%d", &input);
		stack[sp] = input;
		break;
	case 2: //halt code
		code_length = 0;
		break;
	default:
		break;
	}
}

int main(int argc, char **argv)
{

	argc--; argv++;
	char* foo = *argv;
	FILE* fo = fopen(foo, "rb");

	readPM0(fo);
	printCode();
	runPM0();

	return 0;
}
