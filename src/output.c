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
	real_t real = creal(result);
	real_t imag = cimag(result);
	if (imag == 0) {
		printf("%g\n", real);
	} else if (imag == 1) {
		if (real == 0) {
			printf("i\n");
		} else {
			printf("%g+i\n", real);
		}
	} else if (imag == -1) {
		if (real == 0) {
			printf("-i\n");
		} else {
			printf("%g-i\n", real);
		}
	} else {
		if (real == 0) {
			printf("%gi\n", imag);
		} else {
			printf("%g%+gi\n", imag, real);
		}
	}
}

void clean_on(void)
{
	isclean = 1;
}
