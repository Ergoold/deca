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

char advance(void)
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

num_t scan_num(void)
{
	real_t val;
	int len;
	if (!sscanf(line + pos, "%lg%n", &val, &len))
		error("expected number");
	pos += len;
	char next = *(line + pos++);
	if (next == 'i') {
		return CMPLX(0, val);
	} else if (next != '\0') {
		/* we read an actual character, not eol */
		putback();
	}
	return val;
}

scan_ret scan_const(void)
{
	scan_ret ret = {UNKNOWN, {.func = NULL}};
	if (!isalpha(*(line + pos)))
		return ret;

	char *begin = line + pos;
	while (isalpha(*(line + ++pos)));
	char nextchar = *(line + pos);
	*(line + pos) = '\0';

	if (!strcmp(begin, E_C)) {
		ret.tag = NUM;
		ret.value.num = E;
	} else if (!strcmp(begin, PHI_C)) {
		ret.tag = NUM;
		ret.value.num = PHI;
	} else if (!strcmp(begin, PI_C)) {
		ret.tag = NUM;
		ret.value.num = PI;
	} else if (!strcmp(begin, I_C)) {
		ret.tag = NUM;
		ret.value.num = I;
	} else {
		for (int i = 0; i < FUNCTIONS; i++) {
			if (!strcmp(begin, func_names[i])) {
				ret.tag = FUN;
				ret.value.func = func_ptrs[i];
				break;
			}
		}
		if (!strcmp(begin, "log"))
			ret.tag = LOG;
	}

	*(line + pos) = nextchar;
	return ret;
}
