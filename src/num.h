#ifndef NUM_H
#define NUM_H

typedef double num_t;

/* evaluates a function application with an argument */
num_t evalfunc(int, num_t);

/* evaluates an operator with two operands */
num_t eval(num_t, char, num_t);

/* returns the absolute value of a number */
num_t absolute(num_t);

/* scans a number from stdin */
num_t scan_num(void);

#endif /* !NUM_H */
