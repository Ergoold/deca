#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "num.h"
#include "error.h"
#include "input.h"
#include "const.h"

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
	num_t val;
	int len;
	if (!sscanf(line + pos, "%lg%n", &val, &len))
		error("expected number");
	pos += len;
	return val;
}

scan_ret scan_const(void)
{
	scan_ret ret = {1, {0}};
	if (!isalpha(*(line + pos))) {
		error("mathematical constant or function expected");
		return ret;
	}

	char *begin = line + pos;
	while (isalpha(*(line + ++pos)));
	char nextchar = *(line + pos);
	*(line + pos) = '\0';

	if (!strcmp(begin, E_C)) {
		ret.isfunc = 0;
		ret.value.num = E;
	} else if (!strcmp(begin, PHI_C)) {
		ret.isfunc = 0;
		ret.value.num = PHI;
	} else if (!strcmp(begin, PI_C)) {
		ret.isfunc = 0;
		ret.value.num = PI;
	} else if (!strcmp(begin, SIN_C)) {
		ret.value.func = SIN;
	} else if (!strcmp(begin, COS_C)) {
		ret.value.func = COS;
	} else if (!strcmp(begin, TAN_C)) {
		ret.value.func = TAN;
	} else if (!strcmp(begin, COT_C)) {
		ret.value.func = COT;
	} else if (!strcmp(begin, SEC_C)) {
		ret.value.func = SEC;
	} else if (!strcmp(begin, CSC_C)) {
		ret.value.func = CSC;
	} else if (!strcmp(begin, ARCSIN_C)) {
		ret.value.func = ARCSIN;
	} else if (!strcmp(begin, ARCCOS_C)) {
		ret.value.func = ARCCOS;
	} else if (!strcmp(begin, ARCTAN_C)) {
		ret.value.func = ARCTAN;
	} else if (!strcmp(begin, ARCCOT_C)) {
		ret.value.func = ARCCOT;
	} else if (!strcmp(begin, ARCSEC_C)) {
		ret.value.func = ARCSEC;
	} else if (!strcmp(begin, ARCCSC_C)) {
		ret.value.func = ARCCSC;
	} else if (!strcmp(begin, SINH_C)) {
		ret.value.func = SINH;
	} else if (!strcmp(begin, COSH_C)) {
		ret.value.func = COSH;
	} else if (!strcmp(begin, TANH_C)) {
		ret.value.func = TANH;
	} else if (!strcmp(begin, ARSINH_C)) {
		ret.value.func = ARSINH;
	} else if (!strcmp(begin, ARCOSH_C)) {
		ret.value.func = ARCOSH;
	} else if (!strcmp(begin, ARTANH_C)) {
		ret.value.func = ARTANH;
	} else {
		error("unknown mathematical constant or function");
	}

	*(line + pos) = nextchar;
	return ret;
}
