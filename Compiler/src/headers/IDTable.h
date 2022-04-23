#pragma once

#include <string>
#include <vector>
#include <iostream>

using namespace std;

class IDTable
{
private:

	struct Array // Массив
	{
		string name = "";
	};

	struct Var   // Переменная
	{
		string name = "";
	};

	struct Func  // Функция
	{
		string name = "";
	};

	vector<Func> funcIDList;   // Вектор имен функций
	vector<Var> varIDList;     // Вектор названий переменных
	vector<Array> arrayIDList; // Вектор имен массивов

public:
	IDTable() {};
	~IDTable() {};

	bool pushFuncID(string _name, bool initFunc); // Добавление имени функции
	bool findFuncID(string _name);                // Поиск имени функции

	bool pushVarID(string _name, bool init);      // Добавление названия переменной
	bool findVarID(string str);                   // Поиск названия переменной
	void clearVarID() { varIDList.clear(); };     // Отчистка вектора названий переменных

	bool pushArrayID(string _mas, bool init);     // Добавление имени массива
	bool findArrayID(string _name);               // Поиск имени массива
	void clearArrayID() { arrayIDList.clear(); }; // Отчистка вектора названий массивов
};