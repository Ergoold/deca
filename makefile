warnings = -Werror -Wall -Wextra -Wstrict-prototypes

deca: out/deca.o out/error.o out/expr.o out/input.o out/num.o out/output.o
	cc -o bin/deca out/deca.o out/expr.o out/error.o out/input.o out/num.o out/output.o -lm

out/deca.o: src/deca.c
	cc $(warnings) -c -o out/deca.o src/deca.c

out/error.o: src/error.c
	cc $(warnings) -c -o out/error.o src/error.c

out/expr.o: src/expr.c
	cc $(warnings) -c -o out/expr.o src/expr.c

out/input.o: src/input.c
	cc $(warnings) -c -o out/input.o src/input.c

out/num.o: src/num.c
	cc $(warnings) -c -o out/num.o src/num.c

out/output.o: src/output.c
	cc $(warnings) -c -o out/output.o src/output.c

test: deca
	./test.sh

clean:
	rm out/*
