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

/* scans a constant and returns its value */
num_t scan_const(void);

#endif /* !IO_H */
