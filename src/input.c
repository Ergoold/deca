#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <complex.h>
#include "num.h"
#include "error.h"
#include "input.h"
#include "const.h"
#include "funcs.h"

#define MAX_LINE 256

/* the line currently being read */
static char *line;

/* the position of the current character */
static int pos;

token advance(void)
{
	token tok = {ERR, line + pos, NULL};
	char next = nextchar();
	switch (next) {
	case '+':
		tok.kind = ADD;
		break;
	case '-':
		tok.kind = SUB;
		break;
	case '*':
		tok.kind = MUL;
		break;
	case '/':
		tok.kind = DIV;
		break;
	case '%':
		tok.kind = MOD;
		break;
	case '^':
		tok.kind = EXP;
		break;
	case 'v':
		tok.kind = ROOT;
		break;
	case '(':
		tok.kind = OPEN_PAREN;
		break;
	case ')':
		tok.kind = CLOSE_PAREN;
		break;
	case '|':
		tok.kind = ABS;
		break;
	case '\0':
		tok.kind = EOL;
		break;
	default:
		putback();
		if (isdigit(next) || next == '.') {
			scan_num();
		} else if (isalpha(next)) {
			scan_id();
		} else {
			error("unexpected character");
		}
	}
	tok.end = line + pos;
	return tok;
}

char nextchar(void)
{
	char val = ' ';
	while (val == ' ' || val == '\t')
		val = *(line + pos++);
	if (val == '\n') val = '\0'; 
	if (val == '\0') pos--;
	return val;
}

int readln(void)
{
	clearerror();
	fgets(line, MAX_LINE, stdin);
	pos = 0;
	return !feof(stdin);
}

void putback(void)
{
	pos--;
}

void initialize(void)
{
	line = malloc(MAX_LINE);
}

void initwith(char *input)
{
	line = input;
}

void finalize(void)
{
	free(line);
	putchar('\n');
}

void scan_num(void)
{
	int len;
	if (!sscanf(line + pos, "%*lg%n", &len))
		error("expected number");
	pos += len;
}

void scan_id(void)
{
	while (isalpha(*(line + ++pos)));
}
