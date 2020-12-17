#ifndef CONST_H
#define CONST_H

#include <complex.h>

/* 
 * while they are common as extensions, the official c standard does not
 * require defining any of these constants in any standard header
 */
#define E   2.7182818284590452354
#define PHI 1.6180339887498948482
#define PI  3.14159265358979323846
#define I   _Complex_I

/*
 * these are the inputs that are be parsed into the corresponding constant
 * the c is for character, as these are character pointers
 */
#define E_C   "e"
#define PHI_C "phi"
#define PI_C  "pi"
#define I_C   "i"

enum {
	SIN, COS, TAN,
	ARCSIN, ARCCOS, ARCTAN,
	SINH, COSH, TANH,
	ARSINH, ARCOSH, ARTANH,
	LN,
	/* the amount of functions */
	FUNCTIONS
};

#endif /* !CONST_H */
