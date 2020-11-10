#ifndef ERROR_H
#define ERROR_H

/* displays an error message to the user */
void error(char *);

/* tests whether an error has already occurred */
int haderror(void);

/* clears the error status */
void clearerror(void);

#endif /* !ERROR_H */
