#pragma once
#include<map>
#include<iostream>
#include<string>
#include<fstream>
#include "Lex.h"
#include "IDtable.h"
#include "Tree.h"

using namespace std;

class Syntax {

public:
	bool Parse(Node*& root);			   // ������ ��������������� �����������
	Syntax();							   // �����������
	~Syntax() {};						   // ����������
	void RollBack();	                   // �������� � ������������ ���������
	void SaveStatement();				   // ���������� ��������� �������
	void Check();						   // �������� �� ������ ���������
	Tree* Syn(vector<Token> *tokenL);      // �������� ������
	IDTable IdTable;

private:
	bool On_D(Node*& root);                // ����� �������� �������
	bool On_DLIST(Node*& root);            // ������� �������

	bool On_I(Node*& root, bool init);     // �������������
	bool On_FuncId(Node*& root, bool init);// ��� �������
	bool On_N(Node*& root);                // �����
	bool On_MinNI(Node*& root);            // ������� �����
	bool On_BS(Node*& root);               // ������� ������
	bool On_STR(Node*& root);              // ������

	bool On_IF(Node*& root);               // ��������� ��������
	bool On_IFCond(Node*& root);           // ������� ���� ��������� ���������
	bool On_IFCondElse(Node*& root);       // ������� ����� ��������� ���������

	bool On_FOR(Node*& root);              // ����

	bool On_PR(Node*& root);               // �����

	bool On_FUNC(Node*& root);             // �������
	bool On_FuncCond(Node*& root);         // ������� �������

	bool On_CO(Node*& root);               // �������� �� ���������
	bool On_Declar(Node*& root);           // ���������� ���������� � �������
	bool On_Expr(Node*& root);             // ���������� ��� ���������

	bool On_ARR(Node*& root);                  // ������
	bool On_ArrDec(Node*& root);               // ���������� �������
	bool On_ArrId(Node*& root, bool init);     // ��� �������
	bool On_ArrExpr(Node*& root, bool init);   // ������������� �������
	bool On_ArrInExpr(Node*& root);            // ����� �������
	bool On_FindArrId(Node*& root, bool init); // ���������� ����� ��� ������������ �������

	//===========���� ������� ���������==========
	bool On_Group(Node*& root);            // ��������� � �������
	bool On_Mult(Node*& root);             // �������� ������ ����� On_Group
	bool On_Add(Node*& root);              // ���� ����� ����� On_Mult
	bool On_Result(Node*& root);           // ����� On_Add
	bool On_SQR(Node*& root);              // ���������� ������
	bool On_FuncExpr(Node*& root);         // ����� �������

	bool noErr = true;
	int it;				                   // ������� ������ �������
	int saveIt;			                   // ����������� ������
	int brCount = 0;	                   // ���������� ������
	vector<Token> lexList;                 // ������ ������
	int sizeList = 0;	                   // ������ ������� ������
	bool init = false;                     // ���� �������������
};

// ����� ���������� ������ ��������������� �����������
class SynErr {
public:
	inline SynErr(string str)
	{
		cout << "������ ��������������� �����������: " << str << endl;
	}
};