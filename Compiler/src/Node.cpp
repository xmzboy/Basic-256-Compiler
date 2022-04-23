
#include "Node.h"

// ����������
Node::~Node()
{
    for (int it = 0; it < next.size(); it++)
        delete next[it];
}


// ����������� ��� ����� ������
Node::Node(TokenType _type, string _value)
{
    data.type = _type;
    data.value = _value;
}


// ����������� ��� ����� ������
Node::Node(NType _n_type, string _value)
{
    data.n_type = _n_type;
    data.value = _value;
}


// ����� ������
void Node::Trevasale() {
    cout << "�������� � ���� = " << data.value << endl;

    for (auto node : next) {
        if (node)
            node->Trevasale();
    }
}
