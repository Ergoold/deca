warnings = -Werror -Wall -Wextra -Wstrict-prototypes

deca: out/deca.o out/error.o out/expr.o out/io.o out/num.o
	cc -o deca out/deca.o out/expr.o out/error.o out/io.o out/num.o -lm

out/deca.o: src/deca.c
	cc $(warnings) -c -o out/deca.o src/deca.c

out/error.o: src/error.c
	cc $(warnings) -c -o out/error.o src/error.c

out/expr.o: src/expr.c
	cc $(warnings) -c -o out/expr.o src/expr.c

out/io.o: src/io.c
	cc $(warnings) -c -o out/io.o src/io.c

out/num.o: src/num.c
	cc $(warnings) -c -o out/num.o src/num.c

test: deca
	./test.sh

clean:
	rm out/*
