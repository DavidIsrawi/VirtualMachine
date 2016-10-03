#include <stdio.h>

/*PL0 Token Types*/
typedef enum token {
  nulsym = 1, identsym, numbersym, plussym, minussym,
  multsym, slashsym, oddsym, eqsym, neqsym, lessym, leqsym,
  gtrsym, geqsym, lparentsym, rparentsym, commasym, semicolonsym,
  periodsym, becomessym, beginsym, endsym, ifsym, thensym,
  whilesym, dosym, callsym, constsym, varsym, procsym, writesym,
  readsym , elsesym
} token_type;

union lval {
  char *id;
  int num;   // not recognized yet
} lval;

token_type lex() {
  char c;
  // ignore space, tab, newline
  while ((c=getchar()) == ' ' || c== '\t' || c == '\n')
    ;
  if (c == EOF) return nulsym;

  // identifier
  if (isalpha(c)) {
    char sbuf[100], *p = sbuf;
    do {
      *p++ = c;
    } while ((c=getchar()) != EOF && isalnum(c));
    ungetc(c, stdin);
    *p = '\0';
    lval.id = sbuf;
    return idsym;
  }

  switch (c) {
    case '+' :
      return plussym;
    case '*' :
      return multsym;
    case '(' :
      return lparensym;
    case ')' :
      return rparensym;
    default  :
      printf("illegal token\n");
  }
}

main() {
  printf("example lexer\n");
  token_type tok;
  while ((tok=lex()) != nulsym) {
    printf("token type: %d", tok);
    if (tok == idsym) printf(" semantic value: %s", lval.id);
    printf("\n");
  }
}
