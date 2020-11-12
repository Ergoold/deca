#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "num.h"
#include "error.h"
#include "io.h"
#include "const.h"

#define MAX_LINE 256

/* the line currently being read */
static char *line;

/* the position of the current character */
static char pos;

char advance(void)
{
	char val = ' ';
	while (val == ' ' || val == '\t')
		val = *(line + pos++);
	if (val == '\n') val = '\0'; 
	if (val == '\0') pos--;
	return val;
}

int prompt(void)
{
	fputs("deca> ", stdout);
	clearerror();
	fgets(line, MAX_LINE, stdin);
	pos = 0;
	return !feof(stdin);
}

void show(num_t result)
{
	if (!haderror()) printf("= %g\n", result);
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

num_t scan_const(void)
{
	if (!isalpha(*(line + pos))) {
		error("mathematical constant expected");
		return 0;
	}
	int begin = pos;
	while (isalpha(*(line + ++pos)));
	if (!strncmp(line + begin, E_C  , pos - begin)) return E;
	if (!strncmp(line + begin, PHI_C, pos - begin)) return PHI;
	if (!strncmp(line + begin, PI_C , pos - begin)) return PI;
	error("unknown mathematical constant");
	return 0;
}
