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

int stack[MAX_STACK_HEIGHT] = {0, 0, 0};
instruction code[MAX_CODE_LENGTH];
int code_length = 0;

//function declarations
void LIT();
void OPR();
void LOD();
void STO();
void CAL();
void INC();
void JMP();
void JPC();
void SIO();

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

void readPM0()
{
	FILE *fp = fopen("mcode.pm0", "r");
	int op, l, m, i = 0;
	while (fscanf(fp, "%d", &op) != EOF)
	{
		fscanf(fp, "%d", &l);
		fscanf(fp, "%d", &m);

		code[i].op = op;
		code[i].l = l;
		code[i].m = m;
		i++;
	}

	code_length = i;
}

void executePM0()
{
	
}

void printCode()
{
	int i;

	printf("PL/0 code:\n\n");
	for (i = 0; i < code_length; i++)
		printf("%d %s %d %d\n", i, instCode[code[i].op], code[i].l, code[i].m);
	
	printf("\nExecution:\n ");
	printf("\t\t\t\t pc\tbp\tsp\tstack\n");
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
	case 1:
		sp++;
		printf("Enter a value to push onto the stack: ");
		scanf("%d", &input);
		stack[sp] = input;
		break;
	case 2:
		//	halt();
		break;
	default:
		break;
	}
}

int main() {}