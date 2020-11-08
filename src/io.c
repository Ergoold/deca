#include <stdio.h>
#include <stdlib.h>
#include "num.h"
#include "io.h"

#define MAX_LINE 256

/* the line currently being read */
static char *line;

/* the index of the current character */
static char index;

char getop(void)
{
	char op = ' ';
	while (op != '+' && op != '-' && op != '*' && op != '/' && op != '%'
			&& op != '^' && op != ')' && op != '|' && op != '\0')
		op = advance();
	return op;
}

char advance(void)
{
	char val = ' ';
	while (val == ' ' || val == '\t')
		val = *(line + index++);
	if (val == '\0') index--;
	return val;
}

int isdec(char c)
{
	return '0' <= c && c <= '9';
}

void error(char *message)
{
	if (erred != 0) return;
	fprintf(stderr, "deca: %s\n", message);
	erred = 1;
}

int prompt(void)
{
	fputs("deca> ", stdout);
	erred = 0;
	fgets(line, MAX_LINE, stdin);
	index = 0;
	return !feof(stdin);
}

void show(num_t result)
{
	if (!erred) printf("= %g\n", result);
}

void putback(void)
{
	index--;
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
	if (!sscanf(line + index, "%lg%n", &val, &len))
		error("expected number");
	index += len;
	return val;
}
