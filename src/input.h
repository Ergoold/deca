#ifndef IO_H
#define IO_H

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
	int isfunc;
	/* the returned value */
	union {
		/* the number that the constant is equivalent to */
		num_t num;
		/* the id of the function (see const.h) */
		int func;
	} value;
} scan_ret;

/* scans a constant and returns its value */
scan_ret scan_const(void);

#endif /* !IO_H */
