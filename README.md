# deca

![license](https://img.shields.io/github/license/Ergoold/deca)

deca (from desk calculator) is a simple utility that reads and evaluates mathematical expressions.

## Usage

deca can be used to evaluate a single expression at the command line by giving the expression as an argument to deca:

```
$ deca '1 + 1'
= 2
$ 
```

When invoked with no arguments, deca starts in REPL mode, allowing you to type and evaluate multiple commands at your terminal:

```
$ deca
deca> 1 + 1
= 2
deca> 2^8
= 256
deca> ^D
$ 
```

## Features

deca can evaluate any expression using real numbers, addition, subtraction, multiplication, division, exponentiation, parentheses and taking absolute values.

### Planned

The following additional features are currently planned:
 - clean mode (-c), removing prompt and '='
 - interactive mode (-i), starting repl even with arguments
 - evaluation of some elementary functions
 - complex number support
