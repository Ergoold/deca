#ifndef CONST_H
#define CONST_H

#include <math.h>

/* 
 * while they are common as extensions, the official c standard does not
 * require defining any of these constants in any standard header
 */
#define E   2.7182818284590452354
#define PHI 1.6180339887498948482
#define PI  3.14159265358979323846

/*
 * these are the inputs that are be parsed into the corresponding constant
 * the c is for character, as these are character pointers
 */
#define E_C   "e"
#define PHI_C "phi"
#define PI_C  "pi"

enum {
	SIN, COS, TAN, COT, SEC, CSC,
	ARCSIN, ARCCOS, ARCTAN, ARCCOT, ARCSEC, ARCCSC,
	SINH, COSH, TANH,
	ARSINH, ARCOSH, ARTANH
};

/*
 * once again, corresponding inputs
 */
#define SIN_C "sin"
#define COS_C "cos"
#define TAN_C "tan"
#define COT_C "cot"
#define SEC_C "sec"
#define CSC_C "csc"

#define ARCSIN_C "arcsin"
#define ARCCOS_C "arccos"
#define ARCTAN_C "arctan"
#define ARCCOT_C "arccot"
#define ARCSEC_C "arcsec"
#define ARCCSC_C "arccsc"

#define SINH_C "sinh"
#define COSH_C "cosh"
#define TANH_C "tanh"

#define ARSINH_C "arsinh"
#define ARCOSH_C "arcosh"
#define ARTANH_C "artanh"

#endif /* !CONST_H */
