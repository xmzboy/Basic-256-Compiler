#include "CodeGenerator.h"


CodeGenerator::CodeGenerator() :
    headASM{ ".686P\n.model flat, stdcall\n\ninclude \\masm32\\include\\masm32rt.inc\ninclude Macros.txt\n" }
{
	dataASM = "\n.data\n";

    currentBody = &bodyASM;
}


// Главный метод генератора
void CodeGenerator::generateCode(Node* &root)
{
    for (int it = 0; it < root->next.size(); it++)
        if (root->next[it] != NULL)
            checkRule(root->next[it]);
}


// Поиск правила
void CodeGenerator::checkRule(Node*& root)
{
    if (root->data.type == EQUAL)
        setDeclareVarASM(root->next);

    if (root->data.n_type == PRSTART)
        setPrintASM(root);

    if (root->data.n_type == MAS)
        setDeclareArrASM(root->next);

    if (root->data.n_type == FORSTART)
        setForASM(root);

    if (root->data.n_type == FUNCSTART)
        setFunctionASM(root);

    if (root->data.n_type == IFSTART)
        setIfASM(root);
}


// Объявление переменной
void CodeGenerator::setDeclareVarASM(vector<Node*> roots)
{
    string type, data;
        if (roots[0]->data.n_type != ARRID)
        {
            if (currentBody == &bodyASM) {
                if (std::find(mainLocalaVariables.cbegin(), mainLocalaVariables.cend(), roots[0]->data.value) == mainLocalaVariables.cend())
                    mainLocalaVariables.push_back(roots[0]->data.value);
            }
            else if (roots[0]->data.value == curName) {
                setArifASM(roots[1]);
                addLineToBody("TwoRegisterMacros");
                return;
            }
            else {
                if (std::find(funcLocalaVariables.cbegin(), funcLocalaVariables.cend(), roots[0]->data.value) == funcLocalaVariables.cend())
                    funcLocalaVariables.push_back(roots[0]->data.value);
            }
            setArifASM(roots[1]);
            addLineToBody("fstp " + roots[0]->data.value);
        }
        else {
            setArifASM(roots[1]);
            addLineToBody("fld " + roots[0]->next[1]->data.value);
            addLineToBody("FistpEBX");
            addLineToBody("fstp " + roots[0]->next[0]->data.value + " [ ebx * type " + roots[0]->next[0]->data.value + "]");
        }
}


// Выражение
void CodeGenerator::setArifASM(Node* root)
{   
    std::string hexStr;
    switch (root->data.n_type)
    {
    case NType::UMIN: 
        setArifASM(root->next[0]);
        addLineToBody("fchs");
        break;

    case NType::MULT:
        setArifASM(root->next[0]);
        setArifASM(root->next[1]);
        addLineToBody("fmul");
        break;

    case NType::DIVID:
        setArifASM(root->next[0]);
        setArifASM(root->next[1]);
        addLineToBody("fdiv");
        break;

    case NType::PLUSS:
        setArifASM(root->next[0]);
        setArifASM(root->next[1]);
        addLineToBody("fadd");
        break;

    case NType::MIN:
        setArifASM(root->next[0]);
        setArifASM(root->next[1]);
        addLineToBody("fsub");
        break;

    case NType::SQRT:
        setArifASM(root->next[0]);
        addLineToBody("fsqrt");
        break;

    case NType::INDEF:
        addLineToBody("fld " + root->data.value);
        break;

    case NType::FUNCID:
        setArifASM(root->next[0]);
        addLineToBody("TwoRegisterMacros");
        addLineToBody("push edx");
        addLineToBody("push eax");
        addLineToBody("call " + root->data.value);
        addLineToBody("push edx");
        addLineToBody("push eax");
        addLineToBody("fld qword ptr [esp]");
        break;

    case NType::NUMBER:
        hexStr = convertToHex(root->data.value) + "h";
        addLineToBody("push " + hexStr);
        addLineToBody("fld real4 ptr [esp]");
        break;
    default:
        break;
    }
}


// Перевод числа из dec в hex 
string CodeGenerator::convertToHex(string num)
{
    union NtH
    {
        float f;
        unsigned int u;
    };

    NtH h;
    h.f = atof(num.c_str());

    ostringstream os;
    os << hex << h.u; 
    string res = os.str(); 

    return res;
}


// Функция записи в файл
void CodeGenerator::writeInFile(string fileName)
{
    ofstream file;;
    file.open(fileName);
    if (!file){
        throw CodeErr("Ошибка в открытии файла");
    }

    string localVariables;
    for (auto var : mainLocalaVariables) {
        localVariables += "\tlocal " + var + " : real8\n";
    }

    bodyASM = "\nmain proc\n" + localVariables + bodyASM + "\tinkey\n\tinvoke ExitProcess, 0\n";
    bodyASM += "main endp\nend main";

    file << headASM;
    file << dataASM;
    file << ".code\n";
    for (auto func : functionsASM) {
        file << func;
    }
    file << bodyASM;

    file.close();
}


// Добавление созданной строки в текст программы
void CodeGenerator::addLineToBody(string str)
{
    *currentBody += "\t";
    *currentBody += str;
    *currentBody += "\n";
}


// Добавление созданной строки в сегмент данных
void CodeGenerator::addLineToData(string str)
{
    dataASM += "\t";
    dataASM += str;
    dataASM += "\n";
}


// Объявление массива
void CodeGenerator::setDeclareArrASM(vector<Node*> roots)
{
    string data;
        data = roots[0]->data.value + " real8 " + roots[1]->data.value + " dup (0.)";
    addLineToData(data);
}


//вывод
void CodeGenerator::setPrintASM(Node* root)
{
    double d = 0.0;
    stringstream ss(root->next[0]->data.value);
    switch (root->next[0]->data.n_type)
    {
    case INDEF:
        addLineToBody("fld " + root->next[0]->data.value);
        addLineToBody("TwoRegisterMacros");
        addLineToBody("push edx");  
        addLineToBody("push eax");  
        addLineToBody("printf(\"%f\\n\")"); 
        addLineToBody("pop eax");
        addLineToBody("pop eax");
        break;
    case NUMBER:
        
        ss >> d;
        if(d - floor(d) == 0)
            addLineToBody("printf(\"%f\\n\", FP8(" + root->next[0]->data.value + ".0))");
        else
            addLineToBody("printf(\"%f\\n\", FP8(" + root->next[0]->data.value + "))");
        break;
    case STRIN:
        addLineToBody("printf("+ root->next[0]->data.value + ")");
        addLineToBody("printf(\"\\n\")");
        break;
    case ARRID:
        addLineToBody("fld " + root->next[0]->next[1]->data.value);
        addLineToBody("FistpEBX");
        addLineToBody("printf(\"%f\\n\"," + root->next[0]->next[0]->data.value + "[ ebx * Type " + root->next[0]->next[0]->data.value + "])");
        break;
    case FUNCID:
        setArifASM(root->next[0]->next[0]);
        addLineToBody("TwoRegisterMacros");
        addLineToBody("push edx");
        addLineToBody("push eax");
        addLineToBody("call " + root->next[0]->data.value);
        addLineToBody("push edx");
        addLineToBody("push eax");
        addLineToBody("printf(\"%f\\n\")");
        addLineToBody("pop eax");
        addLineToBody("pop eax");
        break;
    default:
        break;
    }
}


// Цикл
void CodeGenerator::setForASM(Node* root)
{   
    double d = 0.0;
    stringstream ss(root->next[1]->data.value);
    std::string endForLabel = "endFor";
    std::string startForLabel = "startFor";
    counter += "1";

    std::string iterId = root->next[0]->next[0]->data.value;
    std::string maxIter = root->next[1]->data.value;

    setDeclareVarASM(root->next[0]->next);
    bodyASM += startForLabel + counter + ":\n";
    ss >> d;
    if (d - floor(d) == 0)
        addLineToBody("fld FP8(" + maxIter + ".0)");
    else
        addLineToBody("fld FP8(" + maxIter + ")");
    addLineToBody("fld " + iterId);
    addLineToBody("fcompp");
    addLineToBody("fstsw ax");
    addLineToBody("sahf");
    addLineToBody("ja " + endForLabel + counter);
    generateCode(root->next[2]);
    addLineToBody("fld1");
    addLineToBody("fld " + iterId);
    addLineToBody("fadd");
    addLineToBody("fstp " + iterId);
    addLineToBody("jmp " + startForLabel + counter);
    bodyASM += endForLabel + counter + ":\n";
}


// Функция
void CodeGenerator::setFunctionASM(Node* root)
{
    curName = root->next[0]->next[0]->data.value;
    currentBody = &funcASM;
    string funcId = root->next[0]->next[0]->data.value;
    string parameter = root->next[0]->next[1]->data.value;
    generateCode(root->next[1]);
    addLineToBody("ret");
    funcASM += funcId + " ENDP\n";

    string localVariables;
    for (auto var : funcLocalaVariables)
        localVariables += "\tlocal " + var + " : REAL8\n";

    funcASM = (funcId + " PROC " + parameter + " : real8\n") + localVariables + funcASM;
    functionsASM.push_back(funcASM);

    currentBody = &bodyASM;
    funcASM.clear();
    funcLocalaVariables.clear();
    curName.clear();
}


// Условный оператор
void CodeGenerator::setIfASM(Node* root)
{
    Node* condition = root->next[1];
    double d = 0.0;
    double dd = 0.0;
    stringstream ssd(root->next[1]->next[0]->data.value);
    stringstream ss(root->next[1]->next[1]->data.value);
    string falseLabel = "IFLABEL" + counter;
    counter += "1";
    string endIfLabel = "IFLABEL" + counter;
    counter += "1";

    if (condition->next[1]->data.n_type == INDEF)
        addLineToBody("fld " + condition->next[1]->data.value);
    else if (condition->next[1]->data.n_type == NUMBER) {
        ss >> d;
        if (d - floor(d) == 0)
            addLineToBody("fld FP8(" + condition->next[1]->data.value + ".0)");
        else
            addLineToBody("fld FP8(" + condition->next[1]->data.value + ")");
    }
    if (condition->next[0]->data.n_type == INDEF)
        addLineToBody("fld " + condition->next[0]->data.value);
    else if (condition->next[0]->data.n_type == NUMBER) {
        ssd >> dd;
        if (dd - floor(dd) == 0)
            addLineToBody("fld FP8(" + condition->next[0]->data.value + ".0)");
        else
            addLineToBody("fld FP8(" + condition->next[0]->data.value + ")");
    }


    addLineToBody("fcompp");
    addLineToBody("fstsw ax");
    addLineToBody("sahf");

    switch (condition->data.n_type)
    {
    case MTHANCOMP:   // >
        addLineToBody("jbe " + falseLabel);
        break;
    case LTHANCOMP:   // <
        addLineToBody("jae " + falseLabel);
        break;
    case MTHAN_EQUAT: // >=
        addLineToBody("jb " + falseLabel);
        break;
    case LTHAN_EQUAT: // <=
        addLineToBody("ja " + falseLabel);
        break;
    case EQUAT:       // =
        addLineToBody("jne " + falseLabel);
        break;
    default:
        break;
    }

    generateCode(root->next[2]);
    addLineToBody("jmp " + endIfLabel);
    *currentBody += falseLabel + ":\n";

    if (root->next.size() > 3)
        generateCode(root->next[3]);

    *currentBody += endIfLabel + ":\n";
}


