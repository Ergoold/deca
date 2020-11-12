#ifndef OUTPUT_H
#define OUTPUT_H

#include "num.h"

/* shows a number on stdout */
void show(num_t);

/* prints the prompt to stdout */
void prompt(void);

/* activate 'clean mode', removing prompts */
void clean(void);

#endif /* !OUTPUT_H */
