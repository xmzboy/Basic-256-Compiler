#pragma once

#include <string>
#include <sstream>
#include <fstream>
#include "Tree.h"
#include "Node.h"

using namespace std;

class CodeGenerator
{
private:
	string *currentBody;							// ������� ����� ������
	string bodyASM;									// ����� ��������� �� ����������
	vector<string> mainLocalaVariables;				// ������ ��� ���������� � �����
	vector<string> funcLocalaVariables;				// ������ ��� ���������� � �������
	string dataASM;									// ������� ��� ������
	string funcASM;									// ������� ��� �������
	string fileName;								// ��� ����� ��� ������ ����������
	const string headASM;							// ��������� ��� �� ����������, ������� ����������� ������ ����
	vector<string> functionsASM;					// ������ �������
	string curName;									// ������� ��� �������
	string counter;									// ������� ��� ����������� ������ �����

	void addLineToBody(string str);					// ���������� ��������� ������ � ����� ���������
	void addLineToData(string str);                 // ���������� ��������� ������ � ������� ������
	string convertToHex(string num);                // ������� ����� �� dec � hex 

	void setArifASM(Node* root);				    // ���������� �������������� ��������
	void setDeclareVarASM(vector<Node*> roots);		// ���������� ����������
	void setDeclareArrASM(vector<Node*> roots);		// ���������� ������� 
	void setPrintASM(Node* root);					// ������
	void setForASM(Node* root);						// ����
	void setFunctionASM(Node* root);				// �������
	void setIfASM(Node* root);				        // �������� ��������

public:
	CodeGenerator();
	~CodeGenerator() {};
	void generateCode(Node* &root);				    // ������� ������� ��������� ����
	void checkRule(Node* &root);				    // ����� �������
	void writeInFile(string fileName);              // ������� ������ � ����
};


//����� ���������� ������ ���������� ����
class CodeErr {
public:
	inline CodeErr(string str)
	{
		cout << "������ ���������� ����: " << str << endl;
	}
};
