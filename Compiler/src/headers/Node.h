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
    Node(TokenType _type, string _value);  // Инициализация лексем
    Node(NType _n_type, string _value);    // Инициализация типа правил
    void Trevasale();                      // Обход дерева
    NodeData data;                         // Данные узла
    vector<Node*> next;                    // Вектор указателей на другие узлы
};