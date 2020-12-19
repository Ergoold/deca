#ifndef FUNCS_H
#define FUNCS_H

#include <complex.h>
#include "num.h"

static char *func_names[] = {
	"sin", "cos", "tan",
	"arcsin", "arccos", "arctan",
	"sinh", "cosh", "tanh",
	"arsinh", "arcosh", "artanh",
	"ln",
};

static num_t (*func_ptrs[])(num_t) = {
	&csin, &ccos, &ctan,
	&casin, &cacos, &catan,
	&csinh, &ccosh, &ctanh,
	&casinh, &cacosh, &catanh,
	&clog,
};

#endif /* !FUNCS_H */
