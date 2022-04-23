#pragma once
#include "Constant.h"
#include "Token.h"

class Node
{
private:
    struct NodeData
    {
        NType n_type = UNDEF;
        TokenType type = UNDEFT;
        string value = "";
    };

public:
    ~Node();
    Node(TokenType _type, string _value);  // ������������� ������
    Node(NType _n_type, string _value);    // ������������� ���� ������
    void Trevasale();                      // ����� ������
    NodeData data;                         // ������ ����
    vector<Node*> next;                    // ������ ���������� �� ������ ����
};