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
	int begin = pos;
	while (isalpha(*(line + ++pos)));
	if (!strncmp(line + begin, E_C  , pos - begin)) {
		ret.isfunc = 0;
		ret.value.num = E;
	} else if (!strncmp(line + begin, PHI_C, pos - begin)) {
		ret.isfunc = 0;
		ret.value.num = PHI;
	} else if (!strncmp(line + begin, PI_C , pos - begin)) {
		ret.isfunc = 0;
		ret.value.num = PI;
	} else if (!strncmp(line + begin, SIN_C, pos - begin)) {
		ret.value.func = SIN;
	} else if (!strncmp(line + begin, COS_C, pos - begin)) {
		ret.value.func = COS;
	} else if (!strncmp(line + begin, TAN_C, pos - begin)) {
		ret.value.func = TAN;
	} else if (!strncmp(line + begin, COT_C, pos - begin)) {
		ret.value.func = COT;
	} else if (!strncmp(line + begin, SEC_C, pos - begin)) {
		ret.value.func = SEC;
	} else if (!strncmp(line + begin, CSC_C, pos - begin)) {
		ret.value.func = CSC;
	} else if (!strncmp(line + begin, ARCSIN_C, pos - begin)) {
		ret.value.func = ARCSIN;
	} else if (!strncmp(line + begin, ARCCOS_C, pos - begin)) {
		ret.value.func = ARCCOS;
	} else if (!strncmp(line + begin, ARCTAN_C, pos - begin)) {
		ret.value.func = ARCTAN;
	} else if (!strncmp(line + begin, ARCCOT_C, pos - begin)) {
		ret.value.func = ARCCOT;
	} else {
		error("unknown mathematical constant or function");
	}
	return ret;
}
