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
	string *currentBody;							// Текущее место записи
	string bodyASM;									// Текст программы на ассемблере
	vector<string> mainLocalaVariables;				// Вектор имён переменных в мэйне
	vector<string> funcLocalaVariables;				// Вектор имён переменных в функции
	string dataASM;									// Сегмент для данных
	string funcASM;									// Сегмент для функций
	string fileName;								// Имя файла для записи результата
	const string headASM;							// Начальный код на ассемблере, который обязательно должен быть
	vector<string> functionsASM;					// Вектор функций
	string curName;									// Текущее имя функции
	string counter;									// Счетчик для правильного вывода меток

	void addLineToBody(string str);					// Добавление созданной строки в текст программы
	void addLineToData(string str);                 // Добавление созданной строки в сегмент данных
	string convertToHex(string num);                // Перевод числа из dec в hex 

	void setArifASM(Node* root);				    // Добавление арифметических операций
	void setDeclareVarASM(vector<Node*> roots);		// Объявления переменной
	void setDeclareArrASM(vector<Node*> roots);		// Объявления массива 
	void setPrintASM(Node* root);					// Вывода
	void setForASM(Node* root);						// Цикл
	void setFunctionASM(Node* root);				// Функция
	void setIfASM(Node* root);				        // Условный оператор

public:
	CodeGenerator();
	~CodeGenerator() {};
	void generateCode(Node* &root);				    // Главная функция генерации кода
	void checkRule(Node* &root);				    // Выбор правила
	void writeInFile(string fileName);              // Функция записи в файл
};


//класс исключение ошибки генератора кода
class CodeErr {
public:
	inline CodeErr(string str)
	{
		cout << "Ошибка генератора кода: " << str << endl;
	}
};
