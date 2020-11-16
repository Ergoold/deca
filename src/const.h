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

/*
 * the value NAN is used to distinguish functions from numeric constants
 */
/* trigonometric functions */
#define SIN 0
#define COS 1
#define TAN 2
#define COT 3
#define SEC 4
#define CSC 5

/*
 * once again, corresponding inputs
 */
#define SIN_C "sin"
#define COS_C "cos"
#define TAN_C "tan"
#define COT_C "cot"
#define SEC_C "sec"
#define CSC_C "csc"

#endif /* !CONST_H */
