#pragma once
#include <iostream>
#include <sstream>


// Типы токенов
enum TokenType
{
    ID,         // Идентификатор
    DIGIT,      // Число
    STR,        // Строка
    PLUS,       // Плюс
    MINUS,      // Минус
    MUL,        // Умножить
    DIV,        // Делить
    LBR,        // Левая скобка
    RBR,        // Правая скобка
    MTHAN,      // Больше
    LTHAN,      // Меньше
    EQUAL,      // Равно
    DOT,        // Точка
    IF,         // Если
    BSLASH,     // \n
    THEN,       // То
    SQR,        // Квадратный корень
    PRINT,      // Вывод
    ELSE,       // Иначе
    END,        // Конец
    WHILE,      // Цикл Пока
    MTHAN_EQUAL, // Больше или равно
    LTHAN_EQUAL, // Меньше или равно
    FOR,        // Цикл Фор
    TO,         // До
    NEXT,       // Следующее
    FUNCTION,   // Функция
    COMMA,      // Запятая
    UNDEFT,     // Неопределенное значение
    DIM,        // Массив
    KLBR,       // [
    KRBR,       // ]
};


// Типы правил
enum NType
{
    START,     // Старт программы
    FUNCSTART, // Начало функции
    EXPR,      // Выражение
    PRSTART,   // Начало вывода
    FORSTART,  // Начало цикла
    EXPRSTART, // Начало выражения
    FORBODY,   // Тело цикла
    FORNEXT,   // Следущее
    DECL,      // Объявление переменной
    MAS,       // Массив
    UNDEF,     // Неопределенное значение
    SQRT,      // Квадратный корень
    IFCN,      // IF
    EQUAT,     // Операция присваивания
    BACKS,     // \n
    NUMBER,    // Число
    INDEF,     // Переменная
    ARROP,     // Переменная массива
    STRIN,     // Строка
    LFBRG,     // (
    RGBRG,     // )
    IFSTART,   // Начало условия
    IFELSE,    // Иначе
    IFBODY,    // Тело IF
    MTHAN_EQUAT, // Больше или равно
    LTHAN_EQUAT, // Меньше или равно
    MTHANCOMP, // Больше
    LTHANCOMP, // Меньше
    FUNCCOND,  // Условие функции
    FUNCID,    // Имя функции
    FUNCBODY,  // Тело функции
    MIN,       // Минус
    UMIN,      // Унарный минус
    PLUSS,     // Плюс
    MULT,      // Умножение
    DIVID,     // Деление
    ARRID,     // Имя массива
};

