#include <math.h>
#include "num.h"
#include "error.h"
#include "const.h"

num_t absolute(num_t n)
{
	return fabs(n);
}

num_t eval(num_t left, char op, num_t right)
{
	switch (op) {
	case '+':
		return left + right;
	case '-':
		return left - right;
	case '*':
		return left * right;
	case '/':
		if (right == 0) {
			error("divided by zero");
			return 0;
		}
		return left / right;
	case '%':
		if (right == 0) {
			error("divided by zero");
			return 0;
		}
		return left / right;
	case '^':
		return pow(left, right);
	case 'v':
		if (right < 0) {
			error("took root of negative number");
			return 0;
		}
		return pow(right, 1 / left);
	default:
		error("unrecognized operator");
		return 0;
	}
}

num_t evalfunc(int func, num_t arg)
{
	switch (func) {
	case SIN:
		return sin(arg);
	case COS:
		return cos(arg);
	case TAN:
		return tan(arg);
	case COT:
		return 1 / tan(arg);
	case SEC:
		return 1 / cos(arg);
	case CSC:
		return 1 / sin(arg);
	default:
		error("unrecognized function");
		return 0;
	}
}
