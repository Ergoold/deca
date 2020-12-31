#include <math.h>
#include <complex.h>
#include "num.h"
#include "error.h"

num_t logarithm(num_t base, num_t arg)
{
	return clog(arg) / clog(base);
}

num_t absolute(num_t n)
{
	return cabs(n);
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
		if (cimag(right) != 0 || cimag(left) != 0) {
			error("performed modulus with complex numbers");
			return 0;
		}
		return fmod(creal(left), creal(right));
	case '^':
		return cpow(left, right);
	case 'v':
		return cpow(right, 1 / left);
	default:
		error("unrecognized operator");
		return 0;
	}
}

int isint(num_t);

num_t call(num_t (*func)(num_t), num_t exponent, num_t arg)
{
	if (!isint(exponent) || creal(exponent) < 0) {
		error("raised function to unnatural power");
		return 0;
	}
	num_t ret = arg;
	for (int i = 0; i < creal(exponent); i++) {
		// we know this ^ is natural due to the check above
		ret = func(ret);
	}
	return ret;
}

int isint(num_t n) {
	if (cimag(n) != 0) return 0;
	real_t a = creal(n);
	return trunc(a) == a;
}
