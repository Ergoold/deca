#include <stddef.h>
#include <ctype.h>
#include "expr.h"
#include "num.h"
#include "error.h"
#include "input.h"

num_t readatom(void);
num_t readplus(num_t, token);
num_t readmult(num_t, token);
num_t readexp(num_t, token);
num_t readunary(token);
num_t readfunc(num_t (*func)(num_t));
num_t readlog(void);

num_t readexpr(void)
{
	num_t val = readatom();
	if (haderror()) return val;

	token op;
	while (op.kind != EOL) {
		op = advance();
		switch (op.kind) {
		case EOL: case CLOSE_PAREN: case ABS: break;
		case ADD: case SUB:
			val = readplus(val, op);
			break;
		case MUL: case DIV: case MOD:
			val = readmult(val, op);
			break;
		case EXP: case ROOT:
			val = readexp(val, op);
			break;
		default:
			error("unrecognized operation");
			break;
		}
	} while (op.kind != EOL);
	putback(op);
	return val;
}

num_t readatom(void)
{
	token tok = advance();
	num_t val;
	switch (tok.kind) {
	case OPEN_PAREN:
		val = readexpr();
		if (advance().kind != CLOSE_PAREN) {
			error("expected ')'");
			return 0;
		}
		return val;
	case ABS:
		val = readexpr();
		if (advance().kind != ABS) {
			error("expected '|'");
			return 0;
		}
		return absolute(val);
	case ADD: case SUB: case ROOT:
		return readunary(tok);
	case NUM:
		return /* todo */;
	case ID:
		return /* todo */;
	default:
			error("expected identifier, '(', '|', '+', '-', or 'v'");
			return 0;
	}
}

num_t readplus(num_t val, token op)
{
	num_t nextval = readatom();
	if (haderror()) return val;
	token nextop = advance();

	switch (nextop.kind) {
	case CLOSE_PAREN: case ABS:
	case ADD: case SUB:
		putback(nextop);
		// fallthrough
	case EOL:
		return eval(val, op, nextval);
	case MUL: case DIV: case MOD:
		nextval = readmult(nextval, nextop);
		return eval(val, op, nextval);
	case EXP: case ROOT:
		nextval = readexp(nextval, nextop);
		return eval(val, op, nextval);
	default:
		error("unrecognized operation");
		return 0;
	}
}

num_t readmult(num_t val, token op)
{
	num_t nextval = readatom();
	if (haderror()) return val;
	token nextop = advance();

	switch (nextop.kind) {
	case CLOSE_PAREN: case ABS:
	case ADD: case SUB:
		putback(nextop);
		// fallthrough
	case EOL:
		return eval(val, op, nextval);
	case MUL: case DIV: case MOD:
		nextval = eval(val, op, nextval);
		return readmult(nextval, nextop);
	case EXP: case ROOT:
		nextval = readexp(nextval, nextop);
		return eval(val, op, nextval);
	default:
		error("unrecognized operation");
		return 0;
	}
}

num_t readexp(num_t val, token op)
{
	num_t nextval = readatom();
	if (haderror()) return val;
	token nextop = advance();

	switch (nextop.kind) {
	case CLOSE_PAREN: case ABS:
	case ADD: case SUB:
	case MUL: case DIV: case MOD:
		putback(nextop);
		// fallthrough
	case EOL:
		return eval(val, op, nextval);
	case EXP: case ROOT:
		nextval = readexp(nextval, nextop);
		return eval(val, op, nextval);
	default:
		error("unrecognized operation");
		return 0;
	}
}

num_t readunary(token op)
{
	num_t implicit_operand = 0;
	if (op.kind == ROOT) implicit_operand = 2;

	num_t val = readatom();
	if (haderror()) return val;
	token nextop = advance();

	switch (nextop.kind) {
	case CLOSE_PAREN: case ABS:
	case ADD: case SUB:
	case MUL: case DIV: case MOD:
		putback(nextop);
		// fallthrough
	case EOL:
		return eval(implicit_operand, op, val);
	case EXP: case ROOT:
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
	token next = advance();
	if (next.kind == '^') {
		exponent = readatom();
	} else {
		/* todo putback */
		putback(next);
	}

	num_t arg = readatom();
	if (haderror()) return 0;

	return call(func, exponent, arg);
}

num_t readlog()
{
	num_t base = readatom();
	if (haderror()) return 0;
	num_t arg = readatom();
	if (haderror()) return 0;

	return logarithm(base, arg);
}
