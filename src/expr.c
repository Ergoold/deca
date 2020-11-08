#include <stdio.h>
#include <stdlib.h>
#include "expr.h"
#include "num.h"
#include "io.h"

num_t readatom(void);
num_t readplus(num_t, char);
num_t readmult(num_t, char);
num_t readexp(num_t, char);
num_t readunary(char);

num_t readexpr(void)
{
	num_t val = readatom();
	if (erred) return val;

	char op = ' ';
	while (op != '\0' && op != ')' && op != '|') {
		op = getop();
		switch (op) {
		case '+': case '-':
			val = readplus(val, op);
			break;
		case '*': case '/': case '%':
			val = readmult(val, op);
			break;
		case '^':
			val = readexp(val, op);
			break;
		}
	}
	putback();
	return val;
}

num_t readatom(void)
{
	char fchar = advance();
	if (!isdec(fchar) && fchar != '.' && fchar != '(' && fchar != '|'
			&& fchar != '+' && fchar != '-') {
		error("expected number, '(', '|', '+' or '-'");
		return 0;
	}

	if (fchar == '(') {
		num_t val = readexpr();
		if (advance() != ')') {
			error("expected ')'");
			return 0;
		}
		return val;
	}

	if (fchar == '|') {
		num_t val = readexpr();
		if (advance() != '|') {
			error("expected '|'");
			return 0;
		}
		return absolute(val);
	}

	if (fchar == '+' || fchar == '-')
		return readunary(fchar);

	putback();
	return scan_num();
}

num_t readplus(num_t val, char op)
{
	num_t nextval = readatom();
	if (erred) return val;
	char nextop = getop();

	switch (nextop) {
	case '\0': case ')': case '|':
	case '+': case '-':
		putback();
		return eval(val, op, nextval);
	case '*': case '/': case '%':
		nextval = readmult(nextval, nextop);
		return eval(val, op, nextval);
	case '^':
		nextval = readexp(nextval, nextop);
		return eval(val, op, nextval);
	default:
		error("unrecognized operation");
		return 0;
	}
}

num_t readmult(num_t val, char op)
{
	num_t nextval = readatom();
	if (erred) return val;
	char nextop = getop();

	switch (nextop) {
	case '\0': case ')': case '|':
	case '+': case '-':
		putback();
		return eval(val, op, nextval);
	case '*': case '/': case '%':
		nextval = readexp(nextval, nextop);
		return eval(val, op, nextval);
	case '^':
		nextval = readexp(nextval, nextop);
		return eval(val, op, nextval);
	default:
		error("unrecognized operation");
		return 0;
	}
}

num_t readexp(num_t val, char op)
{
	num_t nextval = readatom();
	if (erred) return val;
	char nextop = getop();

	switch (nextop) {
	case '\0': case ')': case '|':
	case '+': case '-':
	case '*': case '/': case '%':
		putback();
		return eval(val, op, nextval);
	case '^':
		nextval = readexp(nextval, nextop);
		return eval(val, op, nextval);
	default:
		error("unrecognized operation");
		return 0;
	}
}

num_t readunary(char op)
{
	num_t val = readatom();
	if (erred) return val;
	char nextop = getop();

	switch (nextop) {
	case '\0': case ')': case '|':
	case '+': case '-':
	case '*': case '/': case '%':
		putback();
		return eval(0, op, val);
	case '^':
		val = readexp(val, nextop);
		return eval(0, op, val);
	default:
		error("unrecognized operation");
		return 0;
	}
}
