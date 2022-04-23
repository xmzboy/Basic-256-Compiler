#pragma once
#include <iostream>
#include <sstream>


// ���� �������
enum TokenType
{
    ID,         // �������������
    DIGIT,      // �����
    STR,        // ������
    PLUS,       // ����
    MINUS,      // �����
    MUL,        // ��������
    DIV,        // ������
    LBR,        // ����� ������
    RBR,        // ������ ������
    MTHAN,      // ������
    LTHAN,      // ������
    EQUAL,      // �����
    DOT,        // �����
    IF,         // ����
    BSLASH,     // \n
    THEN,       // ��
    SQR,        // ���������� ������
    PRINT,      // �����
    ELSE,       // �����
    END,        // �����
    WHILE,      // ���� ����
    MTHAN_EQUAL, // ������ ��� �����
    LTHAN_EQUAL, // ������ ��� �����
    FOR,        // ���� ���
    TO,         // ��
    NEXT,       // ���������
    FUNCTION,   // �������
    COMMA,      // �������
    UNDEFT,     // �������������� ��������
    DIM,        // ������
    KLBR,       // [
    KRBR,       // ]
};


// ���� ������
enum NType
{
    START,     // ����� ���������
    FUNCSTART, // ������ �������
    EXPR,      // ���������
    PRSTART,   // ������ ������
    FORSTART,  // ������ �����
    EXPRSTART, // ������ ���������
    FORBODY,   // ���� �����
    FORNEXT,   // ��������
    DECL,      // ���������� ����������
    MAS,       // ������
    UNDEF,     // �������������� ��������
    SQRT,      // ���������� ������
    IFCN,      // IF
    EQUAT,     // �������� ������������
    BACKS,     // \n
    NUMBER,    // �����
    INDEF,     // ����������
    ARROP,     // ���������� �������
    STRIN,     // ������
    LFBRG,     // (
    RGBRG,     // )
    IFSTART,   // ������ �������
    IFELSE,    // �����
    IFBODY,    // ���� IF
    MTHAN_EQUAT, // ������ ��� �����
    LTHAN_EQUAT, // ������ ��� �����
    MTHANCOMP, // ������
    LTHANCOMP, // ������
    FUNCCOND,  // ������� �������
    FUNCID,    // ��� �������
    FUNCBODY,  // ���� �������
    MIN,       // �����
    UMIN,      // ������� �����
    PLUSS,     // ����
    MULT,      // ���������
    DIVID,     // �������
    ARRID,     // ��� �������
};

