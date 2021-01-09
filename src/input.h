#ifndef INPUT_H
#define INPUT_H

#include "token.h"
#include "num.h"

/* reads the next token */
token advance(void);

/* puts the token back into the stream */
void putback(token);

/* reads a new input line; returns 0 on eof */
int readln(void);

/* initializes io */
void initialize(void);

/* initializes io, using a string as the input */
void initwith(char *);

/* finalizes io */
void finalize(void);

#endif /* !INPUT_H */
