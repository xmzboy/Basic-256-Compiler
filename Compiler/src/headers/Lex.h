#pragma once
#include<map>
#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include "Constant.h"
#include "Token.h"

using namespace std;

typedef enum Statement { S0, S1, S2, S3, S4, S5, S6 } Statement; // ���������
typedef enum Output { O0, O1, O2, O3, O4, O5, O6, O7, O8, O9, O10, O11, O12, O13, O14, O15, O16, O17, O18, O19, O20, O21, O22, O23, O24, O25, O26, O27, O28, O29, O30, O31} Output; // �������� �������

extern map<string, Output> Keywords;    // ������� �������� ����
typedef pair<Statement, Output> Result; // ���� ����(���������, �������� ������)
typedef pair<Statement, char> Input;    // ���� ����(������� ���������, ������� ������)
typedef pair<Input, Result> Item;       // ������� ������� ���������
extern map<Input, Result> M;            // ������� ��������� ��������� ��������


void Init(void);                        // ������� ������������� (���������� ������� ��������� ��������� ��������)
void PrintToken(TokenType token);       // ����� ���� �������


// ����� ������������ �����������
class Lex {
public:
    Lex();
    ~Lex();
    bool GetToken(Token& token);                        // ������� ��������� ��������� �������
    vector<Token>* getTokenList() { return &tokenL; };  // ������� ������������ ������ ������

private:
    ifstream _file;                     // �������� �����
    bool isLast, isStrCon;              // �����
    int _position;                      // ��������� �� ����������� �������� ������
    vector<Token> tokenL;               // ������� �������
};


// ����� ������ ������������ �����������
class LexErr {
    public:
        inline LexErr(string str)
        {
            cout << "������ ������������ �����������: " << str << endl;
        }
};