#pragma once
#include<map>
#include<iostream>
#include<string>
#include<fstream>
#include "Lex.h"
#include "IDtable.h"
#include "Tree.h"

using namespace std;

class Syntax {

public:
	bool Parse(Node*& root);			   // Запуск синтаксического анализатора
	Syntax();							   // Конструктор
	~Syntax() {};						   // Деструктор
	void RollBack();	                   // Откатить к сохраненному состоянию
	void SaveStatement();				   // Сохранение состояния каретки
	void Check();						   // Проверка на пустую программу
	Tree* Syn(vector<Token> *tokenL);      // Создание дерева
	IDTable IdTable;

private:
	bool On_D(Node*& root);                // Вызов главного правила
	bool On_DLIST(Node*& root);            // Главное правило

	bool On_I(Node*& root, bool init);     // Идентификатор
	bool On_FuncId(Node*& root, bool init);// Имя функции
	bool On_N(Node*& root);                // Число
	bool On_MinNI(Node*& root);            // Унарный минус
	bool On_BS(Node*& root);               // Перенос строки
	bool On_STR(Node*& root);              // Строка

	bool On_IF(Node*& root);               // Условыный оператор
	bool On_IFCond(Node*& root);           // условие если условного оператора
	bool On_IFCondElse(Node*& root);       // Условие иначе условного оператора

	bool On_FOR(Node*& root);              // Цикл

	bool On_PR(Node*& root);               // Вывод

	bool On_FUNC(Node*& root);             // Функция
	bool On_FuncCond(Node*& root);         // Условие функции

	bool On_CO(Node*& root);               // Проверка на равенство
	bool On_Declar(Node*& root);           // Объявление переменной в условии
	bool On_Expr(Node*& root);             // Объявление или выражение

	bool On_ARR(Node*& root);                  // Массив
	bool On_ArrDec(Node*& root);               // Объявление массива
	bool On_ArrId(Node*& root, bool init);     // Имя массива
	bool On_ArrExpr(Node*& root, bool init);   // Инициализация массива
	bool On_ArrInExpr(Node*& root);            // Вызов массива
	bool On_FindArrId(Node*& root, bool init); // Нахождение имени уже объявленного массива

	//===========БЛОК ФУНКЦИЙ ВЫРАЖЕНИЯ==========
	bool On_Group(Node*& root);            // Выражение в скобках
	bool On_Mult(Node*& root);             // Умножить делить вызов On_Group
	bool On_Add(Node*& root);              // Плюс минус вызов On_Mult
	bool On_Result(Node*& root);           // Вызов On_Add
	bool On_SQR(Node*& root);              // Квадратный корень
	bool On_FuncExpr(Node*& root);         // Вызов функции

	bool noErr = true;
	int it;				                   // Текущий индекс вектора
	int saveIt;			                   // Сохраненный индекс
	int brCount = 0;	                   // Количество скобок
	vector<Token> lexList;                 // Вектор лексем
	int sizeList = 0;	                   // Размер вектора лексем
	bool init = false;                     // Флаг инициализации
};

// Класс исключение ошибки синтаксического анализатора
class SynErr {
public:
	inline SynErr(string str)
	{
		cout << "Ошибка синтаксического анализатора: " << str << endl;
	}
};