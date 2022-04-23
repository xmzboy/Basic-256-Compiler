#pragma once

#include "Lex.h"
#include "Syntax.h"
#include "CodeGenerator.h"


Token token;												 // �������
Tree* tree;													 // ������
Syntax* syn = new Syntax();									 // ������
Lex* lex = new Lex();							             // ����������� ����������
CodeGenerator* codeGen = new CodeGenerator();	             // ��������� ����
//string OutputFile = "C:\\masm32\\AssemblerCheck\\check.asm"; // �������� ����
string OutputFile = "check.asm"; // �������� ����