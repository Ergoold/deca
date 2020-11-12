#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include "input.h"
#include "output.h"
#include "expr.h"

void usage(void);

int main(int argc, char **argv)
{
	int prevind = 1;
	int option;
	do {
		option = getopt(argc, argv, "+:c");
		switch (option) {
		case 'c':
			clean_on();
			break;
		default:
			option = -1;
			optind = prevind;
		}
		prevind = optind;
	} while (option != -1);

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
	exit(2);
}
