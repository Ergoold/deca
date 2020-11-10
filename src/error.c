#include <stdio.h>
#include "error.h"

/* the current error status */
static int erred;

void error(char *message)
{
	if (erred) return;
	fprintf(stderr, "deca: %s\n", message);
	erred = 1;
}

int haderror(void)
{
	return erred;
}

void clearerror(void)
{
	erred = 0;
}
