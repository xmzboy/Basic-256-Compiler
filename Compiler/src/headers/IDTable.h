#pragma once

#include <string>
#include <vector>
#include <iostream>

using namespace std;

class IDTable
{
private:

	struct Array // ������
	{
		string name = "";
	};

	struct Var   // ����������
	{
		string name = "";
	};

	struct Func  // �������
	{
		string name = "";
	};

	vector<Func> funcIDList;   // ������ ���� �������
	vector<Var> varIDList;     // ������ �������� ����������
	vector<Array> arrayIDList; // ������ ���� ��������

public:
	IDTable() {};
	~IDTable() {};

	bool pushFuncID(string _name, bool initFunc); // ���������� ����� �������
	bool findFuncID(string _name);                // ����� ����� �������

	bool pushVarID(string _name, bool init);      // ���������� �������� ����������
	bool findVarID(string str);                   // ����� �������� ����������
	void clearVarID() { varIDList.clear(); };     // �������� ������� �������� ����������

	bool pushArrayID(string _mas, bool init);     // ���������� ����� �������
	bool findArrayID(string _name);               // ����� ����� �������
	void clearArrayID() { arrayIDList.clear(); }; // �������� ������� �������� ��������
};