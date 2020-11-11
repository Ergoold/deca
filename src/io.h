#ifndef IO_H
#define IO_H

#include "num.h"

/* reads the next character */
char advance(void);

/* tests if a character is a decimal digit */
int isdec(char);

/* tests if a character is an english letter */
int isletter(char);

/* prints the prompt to stdout and sets erred to 0; returns 0 on eof */
int prompt(void);

/* prints the result of an expression to stdout */
void show(num_t);

/* puts the last character back into the input */
void putback(void);

/* initializes io */
void initialize(void);

/* initializes io, using a string as the input */
void initwith(char *);

/* finalizes io */
void finalize(void);

/* scans a constant and returns its value */
num_t scan_const(void);

#endif /* !IO_H */
