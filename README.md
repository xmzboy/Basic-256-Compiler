# Compiler for Basic-256

This compiler is open-source, you may use it for compile your .kbs files or as an example for write your own compiler

# Contents
- [How it works](#how-it-works)
- [Requirements](#requirements)
- [Quick start](#quick-start)
- [Architecture](#architecture)
- [Theoretical foundations](#theoretical-foundations)
	- [Description input language](#description-input-language)
	- [Description output language](#description-output-language)
- [Lexical analyzer](#lexical-analyzer)
	- [Description of the lexical analyzer](#description-of-the-lexical-analyzer)
	- [Data structures and processing algorithms](#data-structures-and-processing-algorithms)
- [Syntactic analyzer](#syntactic-analyzer)
	- [Description of the parser](#description-of-the-parser)
	- [Data structures and processing algorithms of parser](#data-structures-and-processing-algorithms-of-parser)
	- [Semantic analysis](#semantic-analysis)
- [Code Generator](#code-generator)
	- [Description of the code generator](#description-of-the-code-generator)
	- [Code generation method](#code-generation-method)
	- [Data structures and processing algorithms in code generator](#data-structures-and-processing-algorithms-in- code-generator)

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

# Theoretical foundations
## Description input language
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

## Description output language
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
Lex(); 				// Constructor, opens the file with the input program
~Lex(); 			// Destructor, closes the file stream.
bool getToken(Token& token); 	// This method takes as an argument a reference to a variable of type Token (created class). This method reads characters from the file and checks which type of tokens the current character can belong to. The method throws an error if the resulting sequence of characters cannot be assigned to any type.
vector<Token>* getTokenList() { return &tokenL; }; // The method returns a vector of lexemes as a result of the lexical analyzer
````
The LexErr error exclusion class is necessary to trigger an exceptional situation.
```c++
-inline LexErr(string str); //the function that is responsible for the output of the exception that occurred
`````

The Lex class contains the following fields:
```c++
ifstream _file; 	// File stream
bool isLast, isStrCon; 	// Flags of the end of the file and the number of quotes
int _position; 		// Pointer to the saved stream fragment
vector<Token> tokenL; 	// Vector of tokens
`````

The Token class contains the string _value and TokenType GetType fields, which store the string value of the token and its type, respectively.
The lexical analyzer also contains the string trim(string&str) function, which is responsible for removing all indents before and after the string constant, if the token is a string constant, otherwise it removes all indents that it sees.

# Syntactic analyzer
## Description of the parser
The parser receives the input result of the lexical analyzer and parses it in accordance with the specified grammar. The main task of the parser is to determine whether the original chain of tokens belongs to the input language.

The parser faces the following tasks:
* checking whether the input string of tokens is grammatically correct for the input language.
* formation of an intermediate representation of the program in the form of a syntactic tree.
* working with the identifier table.

The parser works directly with the chain of lexemes received from the lexical analyzer and checks their suitability to certain rules of the input language. The structure of parser constructs is more complex than the structure of identifiers and numbers. Therefore, to describe the syntax of a language, much more complex grammars are needed compared to regular ones.
For context-free grammar, syntactic analysis is implemented using recursive descent. A procedure is created whose task is, starting from the specified location of the original chain, to find a sub-chain that is derived from a possible nonterminal. If it is not possible to find a hook that satisfies any nonterminal, then the procedure completes its work with an error output.

## Data structures and processing algorithms of parser
During the syntactic analysis, the source text is transformed into a data structure – a tree that displays the syntactic structure of the input sequence and is well suited for further processing.
The parser is written based on the recursive descent method for the input language. It describes the rules and minimum nonterminals for checking the input chain for belonging to the input language.
At the input, the parser receives a chain of tokens in the form of a vector vector<Token> *tokenL;

The Syntax class contains the following methods:
```c++
 bool Parse(Node*& root);			// Running the parser
 Syntax(); 					// Constructor
 ~Syntax() {}; 					// Destructor
 void RollBack(); 				// Roll back to the saved state
 void SaveStatement(); 				// Saving the carriage state
 void Check(); 					// Checking for an empty program
 Tree* Syn(vector<Token> *tokenL); 		// Creating a tree
 bool On_D(Node*& root); 			// Calling the main rule
 bool On_DLIST(Node*& root); 			// Main rule
 bool On_I(Node*& root, bool init); 		// ID processing rule
 bool On_FuncId(Node*& root, bool init); 	// Function name processing rule
 bool On_N(Node*& root); 			// Number processing rule
 bool On_MinNI(Node*&root);			// Unary minus treatment rule
 bool On_BS(Node*& root); 			// Line wrap processing rule
 bool On_STR(Node*& root); 			// String processing rule
 bool On_IF(Node*&root); 			// Conditional operator processing rule
 bool On_IFCond(Node*& root); 			// Rule for processing the condition if conditional operator
 bool On_IFCondElse(Node*& root); 		// Rule for processing a condition of an otherwise conditional operator
 bool On_FOR(Node*& root); 			// Loop processing rule
 bool On_PR(Node*& root); 			// Output processing rule
 bool On_FUNC(Node*& root); 			// Function processing rule
 bool On_FuncCond(Node*& root); 		// Function condition processing rule
 bool On_CO(Node*& root); 			// Equality check rule
 bool On_Declar(Node*& root); 			// Rule variable declaration in condition
 bool On_Expr(Node*& root); 			// Declaration or expression rule
 bool On_Group(Node*& root); 			// Rule for processing expressions in parentheses
 bool On_Mult(Node*& root); 			// Rule for processing multiplication or division calling the On_Group rule(Node*& root);
 bool On_Add(Node*& root); 			// Rule for handling plus or minus calling the On_Mult rule(Node*& root);
 bool On_Result(Node*& root); 			// Calling On_Add(Node*& root);
 bool On_SQR(Node*& root); 			// Square root processing rule
 bool On_FuncExpr(Node*& root); 		// Function call processing rule
 bool On_ARR(Node*& root); 			// Array processing rule
 bool On_ArrDec(Node*& root); 			// Array declaration
 bool On_ArrId(Node*& root, bool init); 	// Array name
 bool On_ArrExpr(Node*& root, bool init); 	// Initializing the array
 bool On_ArrInExpr(Node*& root); 		// Array call
 bool On_FindArrId(Node*& root, bool init); 	// Finding the name of an already declared array
`````

The Syntax class contains the following fields:
```c++
IDTable IDTable; 	// Object of the ID table
int it; 		// Current index of the vector
int saveIt; 		// Saved index
int brCount = 0; 	// Number of brackets
vector<Token> lexList; 	// Vector of lexemes
int sizeList = 0; 	// Size of the token vector
bool init = false; 	// Initialization check
`````
Based on the results of the parser, a tree is built with a bypass root -> left son -> right son. As an example, I give a tree for the line D = b*b - 4*a*m
![Tree_example](https://github.com/xmzboy/Basic-256-Compiler/raw/main/readme_images/Tree_example.png)

## Semantic analysis
The semantic analysis of the input program is also carried out with the help of a parser. With the help of the identifier table, the initialization of a variable, function, or array is checked. Each identifier is added to its corresponding vector, depending on what it is:
```c++
vector<Func> funcIDList; 	// Vector of function names
vector<Var> varIDList; 		// Vector of variable names
vector<Array> arrayIDList; 	// Vector of array names
`````
For each type of identifiers, a search function is performed, or the function of adding an identifier to the corresponding vector.
```c++
 bool pushFuncID(string _name,bool initFunc); 	// Adding a function name
 bool findFuncID(string _name); 		// Function name search
 bool pushVarID(string _name,bool init); 	// Adding a variable name
 bool findVarID(string str); 			// Search for the variable name
 bool pushArrayID(string _mas, bool init); 	// Adding an array name
 bool findArrayID(string _name); 		// Array name search
`````
# Code Generator
## Description of the code generator
Code generation is the last stage of the compiler's work. It should be noted that the assembler uses such a data structure as a stack. It is convenient to count both arithmetic operations and comparison operations on it. The assembler provides opportunities for translating regular languages, but in order to use a context-free language, you must first modify it, as is done when traversing the parse tree.
Assembling may not be the first and not the last step on the way to obtaining an executable program module. So, many compilers from high-level programming languages produce the result in the form of an assembly language program, which is further processed by the assembler. Also, the result of the assembly may not be an executable, but an object module containing disparate blocks of machine code and program data, from which an executable file can be obtained later using the link editor.
It should also be borne in mind that the assembler mainly works with the lowest level of the data hierarchy in the computer, which is why it sometimes has compatibility problems on different operating systems. The matter is complicated by the fact that certain commands are written differently on different processors, for example, commands on Intel may differ significantly from commands on AMD. For example, some processors do not have a division command.
A register is an ultra–fast memory that is located in the processor. Each register has its own purpose, but basically it is data storage, which is implemented by general-purpose registers.
General-purpose registers are used to store a small amount of intermediate data.

![Registers](https://github.com/xmzboy/Basic-256-Compiler/raw/main/readme_images/Registers.png)

* eax – used for storing intermediate data. In fact, it is a universal accumulator of values.
* ebx is the base register that is used to store the address of a given memory block.
* ecx is a counter that is used mainly for cycles.
* esp – stack pointer, contains the address of its vertex.
* edx is a data register that stores intermediate calculations.
* esi is the source index, in chain operations it contains a pointer to the current source element.
* edi is the receiver index, in chain operations it contains a pointer to the current receiver element.
* ebp – stack base pointer.

## Code generation method
Code generation is the compiler's translation of the internal representation of the source program into a string of characters of the output language. Generation generates the resulting object program in assembly language or directly in machine language. The internal representation of a program can have any structure depending on the compiler implementation, while the resulting program is always a linear sequence of commands. Therefore, the generation of object code in any case must perform actions related to the transformation of complex syntactic structures into linear chains.
As a rule, the compiler generates the resulting code in stages based on the completed syntactic constructions of the input program. The compiler extracts a complete syntactic construction from the program text, then generates a fragment of the resulting code for it and places it in the text of the output program. Then it proceeds to the next syntactic construction. This continues until the entire program is disassembled.

## Data structures and processing algorithms in code generator
During the operation of the code generator, the result of the parser, namely the parse tree, is converted into the program text in the MASM32 assembly language. Code generation is divided into three stages. In the first case, the variable declaration is transformed, then the main body of the program is transformed, and after that the functions are transformed if they are available.

The CodeGenerator class contains the following methods:
```c++
void addLineToBody(string str); 		// Adding the created string to the program text
void addLineToData(string str); 		// Adding the created string to the data segment
string convertToHex(string num); 		// Converting a number from dec to hex
void setArifASM(Node* root); 			// Adding arithmetic operations
void setDeclareVarASM(vector<Node*> roots); 	// Variable declaration
void setDeclareArrASM(vector<Node*> roots); 	// Array declaration
void setPrintASM(Node* root); 			// Output
void setForASM(Node* root); 			// Loop
void setFunctionASM(Node* root); 		//Function
void setIfASM(Node* root); 			//Conditional operator
CodeGenerator(); 				// Constructor
~CodeGenerator() {}; 				//Destructor
void GenerateCode(Node* &root); 		// Main code generation function
void writeInFile(string fileName); 		// Write function to file
`````

The CodeGenerator class contains the following fields:
```c++
string *currentBody; 			// The current location
of the string bodyASM entry; 		// The text of the assembler program
vector<string> mainLocalaVariables; 	// Vector of variable names in the main
vector<string> funcLocalaVariables; 	// Vector of variable names in
the string dataASM function; 		// Segment for
string funcASM data; 			// Segment for functions
string fileName; 			// File name for recording the result
const string headASM; 			// The initial code in assembler, which must be
vector<string> functionsASM; 		// Function vector
string curName; 			// Current function name
string counter; 			// Counter for correct label output
`````