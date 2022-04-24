# Compiler for Basic-256

This compiler is open-source, you may use it for compile your .kbs files or as an example for write your own compiler

# Contents
- [How it works](#how-it-works)
- [Requirements](#requirements)
- [Quick start](#quick-start)
- [Architecture](#architecture)
- [Description input language](#description-input-language)
- [Description output language](#description-output-language)

# How it works

The program takes your .kbs or .txt file and runs it through lexical and syntactic analyzers, as well as through a code generator. 
At the output you get an assembler file with the converted code.

# Requirements

* Knowledge of C++

# Quick start

Build the project and enjoy

# Architecture

The compiler have 3 parts:

* 🔊 Lexical analyzer - The lexical analyzer reads and processes the program text line by line and forms lexemes from them, which are passed to the parser
* 🖊 Syntactic analyzer - The parser receives the input result of the lexical analyzer and parses it in accordance with the specified grammar. The main task of the parser is to determine whether the original chain of tokens belongs to the input language.
* 🏗 Code ganerator - Generates assembly code

# Description input language
Basic-256 is a programming language as well as an integrated software development environment developed by Microsoft Corporation.

Input lang alphabet:
* Latin lowercase and uppercase letters (‘A’ – ‘Z’, ‘a’ – ‘z’)
* Digits ‘0’ – ‘9’
* Space
* Other symbols: + - * / = <> ( ) “ [ ] , .

Keywords:
```basic
Print	if	Then	 sqr	Else	end	For
to	Next	function	End	dim	While
`````
Data Types:
* SINGLE - float type	4 bytes

# Description output language
MASM32 is a low–level programming language, which is a format for recording machine commands, convenient for human perception.
Assembly language commands correspond to processor commands and, in fact, represent a convenient symbolic form of writing commands and their arguments. The assembly language also provides basic programming abstractions: linking parts of the program and data through labels with symbolic names and directives.

Output lang alphabet:
* Latin lowercase and uppercase letters (‘A’ – ‘Z’, ‘a’ – ‘z’)
* Digits ‘0’ – ‘9’
* Space
* Operation symbols + - * / = <> ( )  “
* Service symbols

Command set:
* Data forwarding commands (mov, lea)
* Commands for working with the top of the stack, for example, saving (fld, fstp, fistp)
* Arithmetic commands (fadd, fsub, fmul, fdiv);
	* fmul is the multiplication command. It multiplies the ax register by what comes after it. The result is entered in ax.
	* fdiv is the division command. It divides the ax register by what comes after it. The result is entered in ax.
	* fadd is the addition command. Adds two numbers. The result is entered in the first register.
	* fsub is the subtraction command. Subtracts two numbers. The result is entered in the first register.
* fsqrt is the command for taking the square root.
* fchs is the sign change command.
* Logical and bitwise operations (or, and, xor, shr);
* Program progress control commands (jmp, loop, ret, jb, ja, jne);
* Interrupt call commands (int, into);
* Input/output commands to ports (in, out).

Data Types:
* Integer variables in MASM32 can be:
	* 1-byte (8 bits or 1 character), denoted by byte or db;
	* 2-byte (16 bits or 2 characters), denoted by word or dw;
	* 4-byte (32 bits or 4 characters), denoted by dword or dd;
	* 6-byte (48 bits or 6 characters), denoted by fword or df;
	* 8-byte (34 bits or 8 characters), denoted by qword or dq;
	* 10-byte (80 bits or 10 characters), denoted by tword or dt;
* Floating point variables:
	* 4-byte, denoted by real4;
	* 8-byte, denoted by real8;
	* 10-byte, denoted by real10.
