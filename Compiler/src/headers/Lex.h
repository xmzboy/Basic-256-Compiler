#pragma once
#include<map>
#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include "Constant.h"
#include "Token.h"

using namespace std;

typedef enum Statement { S0, S1, S2, S3, S4, S5, S6 } Statement; // Состояния
typedef enum Output { O0, O1, O2, O3, O4, O5, O6, O7, O8, O9, O10, O11, O12, O13, O14, O15, O16, O17, O18, O19, O20, O21, O22, O23, O24, O25, O26, O27, O28, O29, O30, O31} Output; // Выходные сигналы

extern map<string, Output> Keywords;    // Таблица ключевых слов
typedef pair<Statement, Output> Result; // Ключ пара(состояние, выходной сигнал)
typedef pair<Statement, char> Input;    // Ключ пара(каррент состояние, входной символ)
typedef pair<Input, Result> Item;       // Элемент таблицы переходов
extern map<Input, Result> M;            // Таблица переходов конечного автомата


void Init(void);                        // Функция инициализации (заполнение таблицы переходов конечного автомата)
void PrintToken(TokenType token);       // Вывод типа лексемы


// Класс лексического анализатора
class Lex {
public:
    Lex();
    ~Lex();
    bool GetToken(Token& token);                        // Функция получения следующей лексемы
    vector<Token>* getTokenList() { return &tokenL; };  // Функция возвращающая вектор лексем

private:
    ifstream _file;                     // Файловый поток
    bool isLast, isStrCon;              // Флаги
    int _position;                      // Указатель на сохраненный фрагмент потока
    vector<Token> tokenL;               // Таблица токенов
};


// Класс ошибки лексического анализатора
class LexErr {
    public:
        inline LexErr(string str)
        {
            cout << "Ошибка лексического анализатора: " << str << endl;
        }
};