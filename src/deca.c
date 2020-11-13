#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include "input.h"
#include "output.h"
#include "expr.h"

void usage(void);

int main(int argc, char **argv)
{
	int isinteractive = 0;
	int prevind = 1;
	int option;
	do {
		option = getopt(argc, argv, "+:ci");
		switch (option) {
		case 'c':
			clean_on();
			break;
		case 'i':
			isinteractive = 1;
			break;
		default:
			option = -1;
			optind = prevind;
		}
		prevind = optind;
	} while (option != -1);

	switch (argc - optind) {
	case 1:
		initwith(*(argv + optind));
		show(readexpr());
		if (!isinteractive) break;
		// fallthrough
	case 0:
		initialize();
		while (prompt(), readln()) show(readexpr());
		finalize();
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
