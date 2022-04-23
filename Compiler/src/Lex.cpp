#include "Lex.h"

map<Input, Result> M;
map<string, Output> Keywords;


// Вывод типа лексем
void PrintToken(TokenType token) 
{
    switch (token)
    {
        case ID:
            cout << "Тип: ID" << endl;
            break;
        case DIGIT:
            cout << "Тип: DIGIT" << endl;
            break;
        case STR:
            cout << "Тип: STR" << endl;
            break;
        case COMMA:
            cout << "Тип: COMMA" << endl;
            break;
        case PLUS:
            cout << "Тип: PLUS" << endl;
            break;
        case MINUS:
            cout << "Тип: MINUS" << endl;
            break;
        case MUL:
            cout << "Тип: MUL" << endl;
            break;
        case DIV:
            cout << "Тип: DIV" << endl;
            break;
        case LBR:
            cout << "Тип: LBR" << endl;
            break;
        case RBR:
            cout << "Тип: RBR" << endl;
            break;
        case MTHAN:
            cout << "Тип: MTHAN" << endl;
            break;
        case LTHAN:
            cout << "Тип: LTHAN" << endl;
            break;
        case EQUAL:
            cout << "Тип: EQUAL" << endl;
            break;
        case DOT:
            cout << "Тип: DOT" << endl;
            break;
        case IF:
            cout << "Тип: IF" << endl;
            break;
        case BSLASH:
            cout << "Тип: BSLASH" << endl;
            break;
        case KLBR:
            cout << "Тип: KLBR" << endl;
            break;
        case KRBR:
            cout << "Тип: KRBR" << endl;
            break;
        case THEN:
            cout << "Тип: THEN" << endl;
            break;
        case SQR:
            cout << "Тип: SQR" << endl;
            break;
        case PRINT:
            cout << "Тип: PRINT" << endl;
            break;
        case ELSE:
            cout << "Тип: ELSE" << endl;
            break;
        case END:
            cout << "Тип: END" << endl;
            break;
        case WHILE:
            cout << "Тип: WHILE" << endl;
            break;
        case FOR:
            cout << "Тип: FOR" << endl;
            break;
        case TO:
            cout << "Тип: TO" << endl;
            break;
        case NEXT:
            cout << "Тип: NEXT" << endl;
            break;
        case FUNCTION:
            cout << "Тип: FUNCTION" << endl;
            break;
        case DIM:
            cout << "Тип: DIM" << endl;
            break;
        case MTHAN_EQUAL:
            cout << "Тип: MTHAN_EQUAL" << endl;
            break;
        case LTHAN_EQUAL:
            cout << "Тип: LHAN_EQUAL" << endl;
            break;
    }
}


// Конструктор
Lex::Lex() : isLast(false), isStrCon(false) 
{
    const char* fname = "input.txt";
    //открытие файла и ошибка
    _file.open(fname, ifstream::in);
    if (!_file.is_open()) 
        throw LexErr("Ошибка открытия файла");
    _file.unsetf(ios::skipws);
}


// Функция инициализации (заполнение таблицы переходов конечного автомата)
void Init(void)
{
    //Буквы A-Z
    for (int i = 65; i <= 90; i++) {
        M.insert(Item(Input(S0, i), Result(S2, O1)));
        M.insert(Item(Input(S2, i), Result(S2, O1)));
    }
    //Буквы a-z
    for (int i = 97; i <= 122; i++) {
        M.insert(Item(Input(S0, i), Result(S2, O1)));
        M.insert(Item(Input(S2, i), Result(S2, O1)));
    }
    //Цифры 0-9
    for (int i = 48; i <= 57; i++) {
        M.insert(Item(Input(S0, i), Result(S4, O2)));
        M.insert(Item(Input(S4, i), Result(S4, O2)));
        M.insert(Item(Input(S2, i), Result(S2, O1)));
        M.insert(Item(Input(S5, i), Result(S5, O1)));
    }
    //разделители айдишников
    for (int i = 32; i <= 47; i++)
        M.insert(Item(Input(S2, i), Result(S6, O1)));
    for (int i = 59; i <= 63; i++)
        M.insert(Item(Input(S2, i), Result(S6, O1)));
    M.insert(Item(Input(S2, '\n'), Result(S6, O1)));
    M.insert(Item(Input(S2, '\t'), Result(S6, O1)));
    M.insert(Item(Input(S2, '['), Result(S6, O1)));
    M.insert(Item(Input(S2, ']'), Result(S6, O1)));
    M.insert(Item(Input(S2, ','), Result(S6, O1)));
    //разделители чисел
    for (int i = 32; i <= 47; i++) {
        if (i != 46) M.insert(Item(Input(S4, i), Result(S6, O2)));
        M.insert(Item(Input(S5, i), Result(S6, O2)));
    }
    for (int i = 59; i <= 63; i++) {
        M.insert(Item(Input(S4, i), Result(S6, O2)));
        M.insert(Item(Input(S5, i), Result(S6, O2)));
    }
    M.insert(Item(Input(S4, '.'), Result(S5, O2)));
    M.insert(Item(Input(S5, '\n'), Result(S6, O2)));
    M.insert(Item(Input(S5, '\t'), Result(S6, O2)));
    M.insert(Item(Input(S5, '['), Result(S6, O2)));
    M.insert(Item(Input(S5, ']'), Result(S6, O2)));
    M.insert(Item(Input(S4, '\n'), Result(S6, O2)));
    M.insert(Item(Input(S4, '\t'), Result(S6, O2)));
    M.insert(Item(Input(S4, '['), Result(S6, O2)));
    M.insert(Item(Input(S4, ']'), Result(S6, O2)));
    //строковая константа
    M.insert(Item(Input(S0, '"'), Result(S1, O3)));
    M.insert(Item(Input(S1, '"'), Result(S6, O3)));
    for (int i = 65; i <= 90; i++)
        M.insert(Item(Input(S1, i), Result(S1, O3)));
    for (int i = 97; i <= 122; i++)
        M.insert(Item(Input(S1, i), Result(S1, O3)));
    for (int i = 48; i <= 57; i++)
        M.insert(Item(Input(S1, i), Result(S1, O3)));
    for (int i = 32; i <= 47; i++)
        M.insert(Item(Input(S1, i), Result(S1, O3)));
    for (int i = 59; i <= 63; i++)
        M.insert(Item(Input(S1, i), Result(S1, O3)));
    M.insert(Item(Input(S1, '\t'), Result(S1, O3)));
    M.insert(Item(Input(S1, ','), Result(S1, O3)));
    M.insert(Item(Input(S1, '+'), Result(S1, O3)));
    M.insert(Item(Input(S1, '-'), Result(S1, O3)));
    M.insert(Item(Input(S1, '*'), Result(S1, O3)));
    M.insert(Item(Input(S1, '/'), Result(S1, O3)));
    M.insert(Item(Input(S1, '('), Result(S1, O3)));
    M.insert(Item(Input(S1, ')'), Result(S1, O3)));
    M.insert(Item(Input(S1, '['), Result(S1, O3)));
    M.insert(Item(Input(S1, ']'), Result(S1, O3)));
    M.insert(Item(Input(S1, ':'), Result(S1, O3)));
    M.insert(Item(Input(S1, ';'), Result(S1, O3)));
    M.insert(Item(Input(S1, '>'), Result(S1, O3)));
    M.insert(Item(Input(S1, '<'), Result(S1, O3)));
    M.insert(Item(Input(S1, '='), Result(S1, O3)));
    M.insert(Item(Input(S1, '.'), Result(S1, O3)));
    M.insert(Item(Input(S1, '!'), Result(S1, O3)));
    //операторы
    M.insert(Item(Input(S0, '+'), Result(S3, O4)));
    M.insert(Item(Input(S0, '-'), Result(S3, O5)));
    M.insert(Item(Input(S0, '*'), Result(S3, O6)));
    M.insert(Item(Input(S0, '/'), Result(S3, O7)));
    M.insert(Item(Input(S0, '('), Result(S3, O8)));
    M.insert(Item(Input(S0, ')'), Result(S3, O9)));
    M.insert(Item(Input(S0, '>'), Result(S3, O10)));
    M.insert(Item(Input(S0, '<'), Result(S3, O11)));
    M.insert(Item(Input(S0, '='), Result(S3, O12)));
    M.insert(Item(Input(S0, '.'), Result(S3, O13)));
    M.insert(Item(Input(S0, ','), Result(S3, O14)));
    M.insert(Item(Input(S0, '['), Result(S3, O16)));
    M.insert(Item(Input(S0, ']'), Result(S3, O17)));
    //отступы
    M.insert(Item(Input(S0, '\t'), Result(S0, O0)));
    M.insert(Item(Input(S0, ' '), Result(S0, O0)));
    M.insert(Item(Input(S0, '\n'), Result(S6, O15))); 
    //ключевые слова 
    Keywords.insert({"then", Output(O18)});
    Keywords.insert({"sqr", Output(O19)});
    Keywords.insert({"print", Output(O20)});
    Keywords.insert({"else", Output(O21)});
    Keywords.insert({"end", Output(O22)});
    Keywords.insert({"while", Output(O23)});
    Keywords.insert({ "for", Output(O24) });
    Keywords.insert({ "to", Output(O25) });
    Keywords.insert({ "next", Output(O26) });
    Keywords.insert({ "function", Output(O27) });
    Keywords.insert({ "if", Output(O28) });
    Keywords.insert({ "dim", Output(O29) });
    Keywords.insert({ "<=", Output(O30) });
    Keywords.insert({ ">=", Output(O31) });
}


// Удаление отступов. удаляет все отступы до строковой константы и после нее, если лексема - это строковая константа, иначе удаляет все отступы, которые видит
string trim(string& str) 
{
    bool strConst = false;
    string::const_iterator it1 = str.begin();
    while (it1 != str.end()) {
        if (*it1 == '\"')
            strConst = (strConst == true) ? false : true;
        if ((*it1 == ' ' || *it1 == '\t' || *it1 == '\n') && !strConst)
            str.erase(it1);
        else
            it1++;
    }
    return str; // Строка без отступов
}


// Получение лексемы
bool Lex::GetToken(Token& token) 
{
    Statement current = S0; //начальное состояние
    TokenType type;
    string value;
    Result res;
    char symbol;
    map<Input, Result>::const_iterator it; //итератор для таблицы конченого автомата
    map<string, Output>::const_iterator kIt; //итератор для таблицы ключевых слов
    while (!isLast)
    {
        _file.get(symbol);
        if (_file.peek() == EOF) isLast = true;
        //нет пары - тру 
        if (symbol == '\"')
            isStrCon = (isStrCon == true) ? false : true; 
        it = M.find(Input(current, symbol)); //поиск ячейки, соответствующей (current, symbol)
        if (it == M.end()) 
            throw LexErr("Некорректный символ");
        res = it->second; //новая пара (состояние, сигнал)
        //если не буква, не цифра, не строка или не еоф
        if ((res.first != S2 && res.first != S4 && res.first != S5 && res.first != S1 && res.first != S0 )|| isLast) 
        {
            //каррент состояние финальное, либо каррент символ кавычка или перенос стр
            if (res.first != S6 || symbol == '\"' || symbol == '\n' )
                value += symbol;
            if (symbol == '>') {
                char tmp;
                _file.get(tmp);
                if (res.second == O10 && tmp == '=') {
                    value += tmp;
                    res.second = O1;
                    _file.seekg(1, ios::cur);
                }
                else
                    _file.seekg(-1, ios::cur);
            }
            // Проверка на <=
            if (symbol == '<') {
                char tmp;
                _file.get(tmp);
                if (res.second == O11 && tmp == '=') {
                    value += tmp;
                    res.second = O1;
                    _file.seekg(1, ios::cur);
                }
                else
                    _file.seekg(-1, ios::cur);
            }
            switch (res.second) //выходной сигнал
            {
            case O0:
                continue;
                case O1:
                    value = trim(value);
                    kIt = Keywords.find(value); //поиск ячейки в таблице ключевых слов
                    if (kIt == Keywords.end()) //если не нашел, то это обычный айдишник
                        type = ID;
                    else //иначе определяем какое это ключевое слово
                        switch(kIt->second)
                        {
                            case O18:
                                type = THEN; // "then - тогда"
                                break;
                            case O19:
                                type = SQR; // "sqr - корень"
                                break;
                            case O20:
                                type = PRINT; // "print - печать"
                                break;
                            case O21:
                                type = ELSE; // "else - иначе"
                                break;
                            case O22:
                                type = END; // "end - конец"
                                break;
                            case O23:
                                type = WHILE; // "while - пока"
                                break;
                            case O24:
                                type = FOR; // "for - цикл"
                                break;
                            case O25:
                                type = TO; // "to - цикл"
                                break;
                            case O26:
                                type = NEXT; // "next - следующий элемент"
                                break;
                            case O27:
                                type = FUNCTION; // "function - функция"
                                break;
                            case O28:
                                type = IF; // "if - если"
                                break;
                            case O29:
                                type = DIM; // "dim - массив"
                                break;
                            case O30:
                                type = LTHAN_EQUAL; // <=
                                break;
                            case O31:
                                type = MTHAN_EQUAL; // >=
                                break;
                        }
                    break;
                case O2:
                    type = DIGIT; // цифра
                    break;
                case O3:
                    type = STR; // "строка"
                    break;
                case O4:
                    type = PLUS; // +
                    break;
                case O5:
                    type = MINUS; // -
                    break;
                case O6:
                    type = MUL; // *
                    break;
                case O7:
                    type = DIV; // /
                    break;
                case O8:
                    type = LBR; // (
                    break;
                case O9:
                    type = RBR; // )
                    break;
                case O10:
                    type = MTHAN; // >
                    break;
                case O11:
                    type = LTHAN; // <
                    break;
                case O12:
                    type = EQUAL; // =
                    break;
                case O13:
                    type = DOT; // .
                    break;
                case O14:
                    type = COMMA; // ,
                    break;
                case O15:
                    type = BSLASH; // \n
                    break;
                case O16:
                    type = KLBR; // [
                    break;
                case O17:
                    type = KRBR; // ]
                    break;
                default:
                    throw LexErr("Лексическая ошибка");
            }
            //та самая проверка осталась ли кавычка без пары
            if (isStrCon) {
                throw LexErr("Незакрытые кавычки");
            }
            //сформировываем лексему
            token.GetType = type;
            //если лексема не ключевое ключевое слово, то удаляем отступы в этой строке
            if (token.GetType < 18 && token.GetType != 0)
                token._value = trim(value);
            else //если нет то оставляем как есть
                token._value = value;
           tokenL.push_back(token); // Добавляем токен в вектор лексем
            //если лексема не разделитель, то возвращаем захваченный нами лишний символ
            if (!_file.eof() && ((type == ID || type == DIGIT) || (type >= 18 && type <= 31) && (type < 29)))
                _file.seekg(-1, ios::cur); //возвращаем захваченный нами лишний символ
            return true;
        }
        current = res.first; //смена каррент состояния
        value += symbol; //+ строковое значение
    }
    return false;
}


// Деструктор
Lex::~Lex()  
{
    _file.close();
}

