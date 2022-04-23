#pragma once

#include "IDtable.h"
#include "Constant.h"

class Token
{
public:
    string _value;     // Строковое значение
    TokenType GetType; // Тип лексемы
};