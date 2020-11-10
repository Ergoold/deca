#include <math.h>
#include "num.h"
#include "error.h"

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
	default:
		error("unrecognized operator");
		return 0;
	}
}
