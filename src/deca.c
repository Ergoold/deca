#include <stdio.h>
#include "input.h"
#include "output.h"
#include "expr.h"

int main(int argc, char **argv)
{
	switch (argc) {
	case 1:
		initialize();
		while (prompt(), readln()) show(readexpr());
		finalize();
		break;
	case 2:
		initwith(*(argv + 1));
		show(readexpr());
		break;
	default:
		puts("usage: deca [expression]");
	}
}
