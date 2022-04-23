# Compiler for Basic-256

This compiler is open-source, you may use it for compile your .kbs files or as an example for write your own compiler

# Contents
- [How it works](#how-it-works)
- [Requirements](#requirements)
- [Quick start](#quick-start)
- [Architecture](#architecture)

# How it works

The program takes your .kbs or .txt file and runs it through lexical and syntactic analyzers, as well as through a code generator. 
At the output you get an assembler file with the converted code.

# Requirements

* knowledge of C++

# Quick start

Build the project and enjoy

# Architecture

The compiler have 3 containers:

* 🕸 Lexical analyzer - The lexical analyzer reads and processes the program text line by line and forms lexemes from them, which are passed to the parser
* 🏃 Syntactic analyzer - The parser receives the input result of the lexical analyzer and parses it in accordance with the specified grammar. The main task of the parser is to determine whether the original chain of tokens belongs to the input language.
* 🏗 Code ganerator - Generates assembly code


