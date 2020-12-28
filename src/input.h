#ifndef INPUT_H
#define INPUT_H

#include "num.h"

/* reads the next character */
char advance(void);

/* reads a new input line; returns 0 on eof */
int readln(void);

/* puts the last character back into the input */
void putback(void);

/* initializes io */
void initialize(void);

/* initializes io, using a string as the input */
void initwith(char *);

/* finalizes io */
void finalize(void);

/* the return value of the scan_const function */
typedef struct {
	/* the tag for the tagged union */
	int tag;
	/* the returned value */
	/* undefined if tag is not NUM or FUN */
	union {
		/* the number that the constant is equivalent to */
		num_t num;
		/* a pointer to the function */
		num_t (*func)(num_t);
	} value;
} scan_ret;

/* the values of the tag */
#define NUM 0 /* a numeric constant */
#define FUN 1 /* an elementary function */
#define LOG 2 /* two-argument logarithm */
#define UNKNOWN -1 /* an unknown value */

/* scans a constant and returns its value */
scan_ret scan_const(void);

#endif /* !INPUT_H */
