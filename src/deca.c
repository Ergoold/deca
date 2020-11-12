#include <stdio.h>
#include <getopt.h>
#include "input.h"
#include "output.h"
#include "expr.h"

void usage(void);

int main(int argc, char **argv)
{
	int option;
	while ((option = getopt(argc, argv, "+c")) != -1) {
		switch (option) {
		case 'c':
			clean_on();
			break;
		default:
			usage();
		}
	}

	switch (argc - optind) {
	case 0:
		initialize();
		while (prompt(), readln()) show(readexpr());
		finalize();
		break;
	case 1:
		initwith(*(argv + optind));
		show(readexpr());
		break;
	default:
		usage();
	}
}

void usage(void)
{
	puts("usage: deca [-c] [expression]");
}
