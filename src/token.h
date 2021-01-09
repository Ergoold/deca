#ifndef TOKEN_H
#define TOKEN_H

enum token_kind {
	ERR, NUM, ID, ADD, SUB, MUL, DIV, MOD, EXP, ROOT, OPEN_PAREN, CLOSE_PAREN, ABS, EOL
};

typedef struct {
	enum token_kind kind;
	char *start, *end;
} token;

#endif /* !TOKEN_H */
