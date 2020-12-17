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
	double real = creal(result);
	double imag = cimag(result);
	if (real == 0 && imag == 0) {
		printf("0\n");
		return;
	}
	if (real != 0) {
		printf("%g", real);
	}
	if (imag == 1) {
		printf("i\n");
	} else if (imag == -1) {
		printf("-i\n");
	} else if (imag != 0) {
		printf("%+g\n", imag);
	}
}

void clean_on(void)
{
	isclean = 1;
}
