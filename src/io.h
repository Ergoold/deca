#ifndef IO_H
#define IO_H

#include "num.h"

/* this variable is set to 1 when an error occures */
int erred;

/* reads until reaching an operator and returns it */
char getop(void);

/* reads the next character */
char advance(void);

/* tests if a character is a decimal digit */
int isdec(char);

/* prints an error message to stderr and sets erred to 1 */
void error(char *);

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

#endif /* !IO_H */
