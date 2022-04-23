#include "Lex.h"

map<Input, Result> M;
map<string, Output> Keywords;


// ����� ���� ������
void PrintToken(TokenType token) 
{
    switch (token)
    {
        case ID:
            cout << "���: ID" << endl;
            break;
        case DIGIT:
            cout << "���: DIGIT" << endl;
            break;
        case STR:
            cout << "���: STR" << endl;
            break;
        case COMMA:
            cout << "���: COMMA" << endl;
            break;
        case PLUS:
            cout << "���: PLUS" << endl;
            break;
        case MINUS:
            cout << "���: MINUS" << endl;
            break;
        case MUL:
            cout << "���: MUL" << endl;
            break;
        case DIV:
            cout << "���: DIV" << endl;
            break;
        case LBR:
            cout << "���: LBR" << endl;
            break;
        case RBR:
            cout << "���: RBR" << endl;
            break;
        case MTHAN:
            cout << "���: MTHAN" << endl;
            break;
        case LTHAN:
            cout << "���: LTHAN" << endl;
            break;
        case EQUAL:
            cout << "���: EQUAL" << endl;
            break;
        case DOT:
            cout << "���: DOT" << endl;
            break;
        case IF:
            cout << "���: IF" << endl;
            break;
        case BSLASH:
            cout << "���: BSLASH" << endl;
            break;
        case KLBR:
            cout << "���: KLBR" << endl;
            break;
        case KRBR:
            cout << "���: KRBR" << endl;
            break;
        case THEN:
            cout << "���: THEN" << endl;
            break;
        case SQR:
            cout << "���: SQR" << endl;
            break;
        case PRINT:
            cout << "���: PRINT" << endl;
            break;
        case ELSE:
            cout << "���: ELSE" << endl;
            break;
        case END:
            cout << "���: END" << endl;
            break;
        case WHILE:
            cout << "���: WHILE" << endl;
            break;
        case FOR:
            cout << "���: FOR" << endl;
            break;
        case TO:
            cout << "���: TO" << endl;
            break;
        case NEXT:
            cout << "���: NEXT" << endl;
            break;
        case FUNCTION:
            cout << "���: FUNCTION" << endl;
            break;
        case DIM:
            cout << "���: DIM" << endl;
            break;
        case MTHAN_EQUAL:
            cout << "���: MTHAN_EQUAL" << endl;
            break;
        case LTHAN_EQUAL:
            cout << "���: LHAN_EQUAL" << endl;
            break;
    }
}


// �����������
Lex::Lex() : isLast(false), isStrCon(false) 
{
    const char* fname = "input.txt";
    //�������� ����� � ������
    _file.open(fname, ifstream::in);
    if (!_file.is_open()) 
        throw LexErr("������ �������� �����");
    _file.unsetf(ios::skipws);
}


// ������� ������������� (���������� ������� ��������� ��������� ��������)
void Init(void)
{
    //����� A-Z
    for (int i = 65; i <= 90; i++) {
        M.insert(Item(Input(S0, i), Result(S2, O1)));
        M.insert(Item(Input(S2, i), Result(S2, O1)));
    }
    //����� a-z
    for (int i = 97; i <= 122; i++) {
        M.insert(Item(Input(S0, i), Result(S2, O1)));
        M.insert(Item(Input(S2, i), Result(S2, O1)));
    }
    //����� 0-9
    for (int i = 48; i <= 57; i++) {
        M.insert(Item(Input(S0, i), Result(S4, O2)));
        M.insert(Item(Input(S4, i), Result(S4, O2)));
        M.insert(Item(Input(S2, i), Result(S2, O1)));
        M.insert(Item(Input(S5, i), Result(S5, O1)));
    }
    //����������� ����������
    for (int i = 32; i <= 47; i++)
        M.insert(Item(Input(S2, i), Result(S6, O1)));
    for (int i = 59; i <= 63; i++)
        M.insert(Item(Input(S2, i), Result(S6, O1)));
    M.insert(Item(Input(S2, '\n'), Result(S6, O1)));
    M.insert(Item(Input(S2, '\t'), Result(S6, O1)));
    M.insert(Item(Input(S2, '['), Result(S6, O1)));
    M.insert(Item(Input(S2, ']'), Result(S6, O1)));
    M.insert(Item(Input(S2, ','), Result(S6, O1)));
    //����������� �����
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
    //��������� ���������
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
    //���������
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
    //�������
    M.insert(Item(Input(S0, '\t'), Result(S0, O0)));
    M.insert(Item(Input(S0, ' '), Result(S0, O0)));
    M.insert(Item(Input(S0, '\n'), Result(S6, O15))); 
    //�������� ����� 
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


// �������� ��������. ������� ��� ������� �� ��������� ��������� � ����� ���, ���� ������� - ��� ��������� ���������, ����� ������� ��� �������, ������� �����
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
    return str; // ������ ��� ��������
}


// ��������� �������
bool Lex::GetToken(Token& token) 
{
    Statement current = S0; //��������� ���������
    TokenType type;
    string value;
    Result res;
    char symbol;
    map<Input, Result>::const_iterator it; //�������� ��� ������� ��������� ��������
    map<string, Output>::const_iterator kIt; //�������� ��� ������� �������� ����
    while (!isLast)
    {
        _file.get(symbol);
        if (_file.peek() == EOF) isLast = true;
        //��� ���� - ��� 
        if (symbol == '\"')
            isStrCon = (isStrCon == true) ? false : true; 
        it = M.find(Input(current, symbol)); //����� ������, ��������������� (current, symbol)
        if (it == M.end()) 
            throw LexErr("������������ ������");
        res = it->second; //����� ���� (���������, ������)
        //���� �� �����, �� �����, �� ������ ��� �� ���
        if ((res.first != S2 && res.first != S4 && res.first != S5 && res.first != S1 && res.first != S0 )|| isLast) 
        {
            //������� ��������� ���������, ���� ������� ������ ������� ��� ������� ���
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
            // �������� �� <=
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
            switch (res.second) //�������� ������
            {
            case O0:
                continue;
                case O1:
                    value = trim(value);
                    kIt = Keywords.find(value); //����� ������ � ������� �������� ����
                    if (kIt == Keywords.end()) //���� �� �����, �� ��� ������� ��������
                        type = ID;
                    else //����� ���������� ����� ��� �������� �����
                        switch(kIt->second)
                        {
                            case O18:
                                type = THEN; // "then - �����"
                                break;
                            case O19:
                                type = SQR; // "sqr - ������"
                                break;
                            case O20:
                                type = PRINT; // "print - ������"
                                break;
                            case O21:
                                type = ELSE; // "else - �����"
                                break;
                            case O22:
                                type = END; // "end - �����"
                                break;
                            case O23:
                                type = WHILE; // "while - ����"
                                break;
                            case O24:
                                type = FOR; // "for - ����"
                                break;
                            case O25:
                                type = TO; // "to - ����"
                                break;
                            case O26:
                                type = NEXT; // "next - ��������� �������"
                                break;
                            case O27:
                                type = FUNCTION; // "function - �������"
                                break;
                            case O28:
                                type = IF; // "if - ����"
                                break;
                            case O29:
                                type = DIM; // "dim - ������"
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
                    type = DIGIT; // �����
                    break;
                case O3:
                    type = STR; // "������"
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
                    throw LexErr("����������� ������");
            }
            //�� ����� �������� �������� �� ������� ��� ����
            if (isStrCon) {
                throw LexErr("���������� �������");
            }
            //�������������� �������
            token.GetType = type;
            //���� ������� �� �������� �������� �����, �� ������� ������� � ���� ������
            if (token.GetType < 18 && token.GetType != 0)
                token._value = trim(value);
            else //���� ��� �� ��������� ��� ����
                token._value = value;
           tokenL.push_back(token); // ��������� ����� � ������ ������
            //���� ������� �� �����������, �� ���������� ����������� ���� ������ ������
            if (!_file.eof() && ((type == ID || type == DIGIT) || (type >= 18 && type <= 31) && (type < 29)))
                _file.seekg(-1, ios::cur); //���������� ����������� ���� ������ ������
            return true;
        }
        current = res.first; //����� ������� ���������
        value += symbol; //+ ��������� ��������
    }
    return false;
}


// ����������
Lex::~Lex()  
{
    _file.close();
}

