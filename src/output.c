#include <stdio.h>
#include "output.h"
#include "error.h"
#include "num.h"

/* whether clean mode is activated */
static int isclean = 0;

void prompt(void)
{
	if (!isclean) fputs("deca> ", stdout);
}

void show(num_t result)
{
	if (haderror()) return;
	if (!isclean) fputs("= ", stdout);
	printf("%g\n", result);
}

void clean_on(void)
{
	isclean = 1;
}
