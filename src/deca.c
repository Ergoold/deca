#include <stdio.h>
#include "io.h"
#include "expr.h"

int main(int argc, char **argv)
{
	switch (argc) {
	case 1:
		initialize();
		while (prompt()) show(readexpr());
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
