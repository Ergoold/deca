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
	if (imag == 0) {
		printf("%g\n", real);
	} else if (real == 0) {
		if (imag == 1) {
			printf("i\n");
		} else if (imag == -1) {
			printf("-i\n");
		} else {
			printf("%gi\n", imag);
		}
	} else {
		if (imag == 1) {
			printf("%g+i\n", real);
		} else if (imag == -1) {
			printf("%g-i\n", real);
		} else {
			printf("%g%+gi\n", imag, real);
		}
	}
}

void clean_on(void)
{
	isclean = 1;
}
