#ifndef FUNCS_H
#define FUNCS_H

#include <math.h>

static char *func_names[] = {
	"sin", "cos", "tan",
	"arcsin", "arccos", "arctan",
	"sinh", "cosh", "tanh",
	"arsinh", "arcosh", "artanh",
	"ln",
};

static double (*func_ptrs[])(double) = {
	&sin, &cos, &tan,
	&asin, &acos, &atan,
	&sinh, &cosh, &tanh,
	&asinh, &acosh, &atanh,
	&log,
};

#endif /* !FUNCS_H */
