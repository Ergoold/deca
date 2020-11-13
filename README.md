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

### Command-Line Options

deca accepts the following command-line options:

 - `-c`
   
   Activate *Clean Mode*, which does not print the repl prompt or the `= ` sign before results

 - `-i`
   
   Activate *Interactive Mode*, which opens the repl. This mode is active by default if no non-option command-line arguments are provided.

## Features

deca can evaluate any expression using real numbers, addition, subtraction, multiplication, division, exponentiation, parentheses and taking absolute values.

### Planned

The following additional features are currently planned:
 - evaluation of some elementary functions
 - complex number support
