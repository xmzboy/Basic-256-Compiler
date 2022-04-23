
#include "Node.h"

// Деструктор
Node::~Node()
{
    for (int it = 0; it < next.size(); it++)
        delete next[it];
}


// Конструктор для типов лексем
Node::Node(TokenType _type, string _value)
{
    data.type = _type;
    data.value = _value;
}


// Конструктор для типов правил
Node::Node(NType _n_type, string _value)
{
    data.n_type = _n_type;
    data.value = _value;
}


// Обход дерева
void Node::Trevasale() {
    cout << "Значение в узле = " << data.value << endl;

    for (auto node : next) {
        if (node)
            node->Trevasale();
    }
}
