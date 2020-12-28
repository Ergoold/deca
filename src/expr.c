#include <stddef.h>
#include <ctype.h>
#include "expr.h"
#include "num.h"
#include "error.h"
#include "input.h"

num_t readatom(void);
num_t readplus(num_t, char);
num_t readmult(num_t, char);
num_t readexp(num_t, char);
num_t readunary(char);
num_t readfunc(num_t (*func)(num_t));
num_t readlog(void);

num_t readexpr(void)
{
	num_t val = readatom();
	if (haderror()) return val;

	char op = ' ';
	while (op != '\0' && op != ')' && op != '|') {
		op = advance();
		switch (op) {
		case '\0': case ')': case '|': break;
		case '+': case '-':
			val = readplus(val, op);
			break;
		case '*': case '/': case '%':
			val = readmult(val, op);
			break;
		case '^': case 'v':
			val = readexp(val, op);
			break;
		default:
			error("unrecognized operation");
			break;
		}
	}
	putback();
	return val;
}

num_t readatom(void)
{
	char fchar = advance();
	switch (fchar) {
	num_t val;
	case '(':
		val = readexpr();
		if (advance() != ')') {
			error("expected ')'");
			return 0;
		}
		return val;
	case '|':
		val = readexpr();
		if (advance() != '|') {
			error("expected '|'");
			return 0;
		}
		return absolute(val);
	case '+': case '-': case 'v':
		return readunary(fchar);
	default:
		if (isdigit(fchar) || fchar == '.') {
			putback();
			return scan_num();
		} else if (isalpha(fchar)) {
			putback();
			scan_ret token = scan_const();
			switch (token.tag) {
				case NUM:
					return token.value.num;
				case FUN:
					return readfunc(token.value.func);
				case LOG:
					return readlog();
				default:
					error("expected constant or function");
					return 0;
			}
		} else {
			error("expected number, function, '(', '|', '+', '-', or 'v'");
			return 0;
		}
	}
}

num_t readplus(num_t val, char op)
{
	num_t nextval = readatom();
	if (haderror()) return val;
	char nextop = advance();

	switch (nextop) {
	case ')': case '|':
	case '+': case '-':
		putback();
		// fallthrough
	case '\0':
		return eval(val, op, nextval);
	case '*': case '/': case '%':
		nextval = readmult(nextval, nextop);
		return eval(val, op, nextval);
	case '^': case 'v':
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
	if (haderror()) return val;
	char nextop = advance();

	switch (nextop) {
	case ')': case '|':
	case '+': case '-':
		putback();
		// fallthrough
	case '\0':
		return eval(val, op, nextval);
	case '*': case '/': case '%':
		nextval = readexp(nextval, nextop);
		return eval(val, op, nextval);
	case '^': case 'v':
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
	if (haderror()) return val;
	char nextop = advance();

	switch (nextop) {
	case ')': case '|':
	case '+': case '-':
	case '*': case '/': case '%':
		putback();
		// fallthrough
	case '\0':
		return eval(val, op, nextval);
	case '^': case 'v':
		nextval = readexp(nextval, nextop);
		return eval(val, op, nextval);
	default:
		error("unrecognized operation");
		return 0;
	}
}

num_t readunary(char op)
{
	num_t implicit_operand = 0;
	if (op == 'v') implicit_operand = 2;

	num_t val = readatom();
	if (haderror()) return val;
	char nextop = advance();

	switch (nextop) {
	case ')': case '|':
	case '+': case '-':
	case '*': case '/': case '%':
		putback();
		// fallthrough
	case '\0':
		return eval(implicit_operand, op, val);
	case '^': case 'v':
		val = readexp(val, nextop);
		return eval(implicit_operand, op, val);
	default:
		error("unrecognized operation");
		return 0;
	}
}

num_t readfunc(num_t (*func)(num_t))
{
	if (func == NULL) return 0;

	num_t exponent = 1;
	if (advance() == '^') {
		exponent = readatom();
	} else {
		putback();
	}

	num_t arg = readatom();
	if (haderror()) return 0;
	char nextop = advance();

	switch (nextop) {
	case ')': case '|':
	case '+': case '-':
		putback();
		// fallthrough
	case '\0':
		return call(func, exponent, arg);
	case '*': case '/': case '%':
		arg = readmult(arg, nextop);
		return call(func, exponent, arg);
	case '^': case 'v':
		arg = readmult(arg, nextop);
		return call(func, exponent, arg);
	default:
		error("unrecognized operation");
		return 0;
	}
}

num_t readlog()
{
	num_t base = readatom();
	if (haderror()) return 0;
	num_t arg = readatom();
	if (haderror()) return 0;
	char nextop = advance();

	switch (nextop) {
	case ')': case '|':
	case '+': case '-':
		putback();
		// fallthrough
	case '\0':
		return logarithm(base, arg);
	case '*': case '/': case '%':
		arg = readmult(arg, nextop);
		return logarithm(base, arg);
	case '^': case 'v':
		arg = readmult(arg, nextop);
		return logarithm(base, arg);
	default:
		error("unrecognized operation");
		return 0;
	}
}
