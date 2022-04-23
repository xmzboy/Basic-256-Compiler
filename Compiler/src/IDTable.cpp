#include "IDTable.h"


// Добавление имени функции
bool IDTable::pushFuncID(string _name, bool initFunc)
{
	if (!initFunc) {
		if (findFuncID(_name))
			return true;
	}
	else {
		cout << "+++++++++++++++++++++++++++++" << endl;
		cout << "ADD FUNCTION = " << _name << endl;
		cout << "+++++++++++++++++++++++++++++" << endl;
		Func func;
		func.name = _name;

		funcIDList.push_back(func);
		return true;
	}
	return false;
}


// Поиск имени функции
bool IDTable::findFuncID(string _name)
{
	for (int i = 0; i < funcIDList.size(); i++)
	{
		if (_name == funcIDList[i].name) {
			cout << "*-*-*-*-*-*-*-*-*-*-*-*-*" << endl;
			cout << "FIND FUNCTION = " << _name << endl;
			cout << "*-*-*-*-*-*-*-*-*-*-*-*-*" << endl;
			return true;
		}
			
	}
	return false;
}

//========== ПЕРЕМЕННЫЕ ==============//

// Добавление названия переменной
bool IDTable::pushVarID(string _name, bool init)
{
	if (!init) {
		if (findVarID(_name))
			return true;
	}
	else {
		if (pushFuncID(_name, init = false))
			return true;
		else if (pushArrayID(_name, init = false))
			return true;
		cout << "+++++++++++++++++++++++++++++" << endl;
		cout << "ADD VARIABLE = " << _name << endl;
		cout << "+++++++++++++++++++++++++++++" << endl;
		Var var;
		var.name = _name;
		varIDList.push_back(var);
		return true;
	}
	return false;
}


// Поиск названия переменной
bool IDTable::findVarID(string _name)
{
	for (int i = 0; i < varIDList.size(); i++)
	{
		if (_name == varIDList[i].name) {
			cout << "*-*-*-*-*-*-*-*-*-*-*-*-*" << endl;
			cout << "FIND VARIABLE = " << _name << endl;
			cout << "*-*-*-*-*-*-*-*-*-*-*-*-*" << endl;
			return true;
		}

	}
	return false;
}

//========== МАССИВЫ ==============//

// Добавление имени массива
bool IDTable::pushArrayID(string _name, bool init)
{
	if (!init) {
		if (findArrayID(_name))
			return true;
	}
	else {
		cout << "+++++++++++++++++++++++++++++" << endl;
		cout << "ADD ARRAY = " << _name << endl;
		cout << "+++++++++++++++++++++++++++++" << endl;
		Array mas;
		mas.name = _name;

		arrayIDList.push_back(mas);
		return true;
	}
	return false;
}


// Поиск имени массива
bool IDTable::findArrayID(string _name)
{
	for (int i = 0; i < arrayIDList.size(); i++)
	{
		if (_name == arrayIDList[i].name) {
			cout << "*-*-*-*-*-*-*-*-*-*-*-*-*" << endl;
			cout << "FIND ARRAY = " << _name << endl;
			cout << "*-*-*-*-*-*-*-*-*-*-*-*-*" << endl;
			return true;
		}
	}

	return false;
}