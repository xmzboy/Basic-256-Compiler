# Compiler for Basic-256

This compiler is open-source, you may use it for compile your .kbs files or as an example for write your own compiler

# Contents
- [How it works](#how-it-works)
- [Requirements](#requirements)
- [Quick start](#quick-start)
- [Architecture](#architecture)
- [Description input language](#description-input-language)
- [Description output language](#description-output-language)
- [Lexical analyzer](#lexical-analyzer)
- [Description of the lexical analyzer](##description-of-the-lexical-analyzer)
- [Data structures and processing algorithms](##data-structures-and-processing-algorithms)

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

# Lexical analyzer

## Description of the lexical analyzer
The lexical analyzer reads and processes the program text line by line and forms lexemes from them, which are passed to the parser. A lexeme is the minimum indivisible lexical unit of a language.

The lexical analyzer is an optional compilation step, but desirable for the following reasons:
* Checking identifiers, constants, limiters and service words makes the program more convenient for further processing
* The lexical analyzer reduces the length of the program, eliminating insignificant spaces and comments from its original presentation
* If the encoding in the original representation of the program is changed, this will only affect the lexical analyzer

In procedural languages , lexemes are usually divided into classes:
* Constants
* Literals
* Operators and separators
* Identifiers
* Keywords

## Data structures and processing algorithms
The simplest lexical analyzer that recognizes identifiers and numeric constants is represented as a deterministic finite automaton with the following diagram of states and transitions :
![Index](https://github.com/xmzboy/Basic-256-Compiler/raw/main/readme_images/LA.jpg)

Tokens are stored in map, a standard template class of the C++ programming language library designed to implement a mapping abstraction in the form of an ordered associative container. Before adding another token to the container, you need to check it for compliance with the rules, which is what the Lex class is designed for.
The Lex class contains the following methods:
```c++
Lex(); // Constructor, opens the file with the input program
~Lex(); // Destructor, closes the file stream.
bool getToken(Token& token); // This method takes as an argument a reference to a variable of type Token (created class). This method reads characters from the file and checks which type of tokens the current character can belong to. The method throws an error if the resulting sequence of characters cannot be assigned to any type.
vector<Token>* getTokenList() { return &tokenL; }; // The method returns a vector of lexemes as a result of the lexical analyzer
````
The LexErr error exclusion class is necessary to trigger an exceptional situation.
```c++
-inline LexErr(string str); //the function that is responsible for the output of the exception that occurred
`````

The Lex class contains the following fields:
```c++
ifstream _file; // File stream
bool isLast, isStrCon; // Flags of the end of the file and the number of quotes
int _position; // Pointer to the saved stream fragment
vector<Token> tokenL; // Vector of tokens
`````

The Token class contains the string _value and TokenType GetType fields, which store the string value of the token and its type, respectively.
The lexical analyzer also contains the string trim(string&str) function, which is responsible for removing all indents before and after the string constant, if the token is a string constant, otherwise it removes all indents that it sees.