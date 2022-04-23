#pragma once

#include "Lex.h"
#include "Syntax.h"
#include "CodeGenerator.h"


Token token;												 // Лексема
Tree* tree;													 // Дерево
Syntax* syn = new Syntax();									 // Парсер
Lex* lex = new Lex();							             // Лексический анализатор
CodeGenerator* codeGen = new CodeGenerator();	             // Генератор кода
//string OutputFile = "C:\\masm32\\AssemblerCheck\\check.asm"; // Выходной файл
string OutputFile = "check.asm"; // Выходной файл