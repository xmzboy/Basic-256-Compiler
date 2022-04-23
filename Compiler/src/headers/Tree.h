#pragma once
#include<map>
#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include "Token.h"
#include "Node.h"

class Tree
{
public:
	Node* root;
	~Tree() {};
	Tree() {};

	void Trev() {
		root->Trevasale();
	}
};