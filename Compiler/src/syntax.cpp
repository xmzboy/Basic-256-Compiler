#include "Syntax.h"
#define err {noErr = false; return false;}


//инициализация и проверка
Syntax::Syntax()
{
	it = -1;
	saveIt = -1;
}


//возвращение к сохраненному индексу вектора
void Syntax::RollBack()
{
	it = saveIt;
}


//сохранение индекса вектора
void Syntax::SaveStatement()
{
	saveIt = it;
}


//проверка 
void Syntax::Check()
{
	auto it = lexList.begin();
	while (it->GetType == BSLASH)
	{
		//удаление \n
		it = lexList.erase(it);
		// Если вдруг программа состоит только из \n
		if (it == lexList.end()) throw SynErr("Программа не имеет операторов.");
	}
}


// Создание дерева
Tree* Syntax::Syn(vector<Token>* tokenL)
{
	lexList = *tokenL;
	sizeList = tokenL->size();
	Check();
	Tree* tree = new Tree();
	Parse(tree->root);
	return tree;
}


// Запуск синтаксического анализатора
bool Syntax::Parse(Node*& root)
{
	Node* child;
	root = new Node(START,"START");
	bool successComp = false;
	successComp = On_D(root);
	if (successComp && noErr) {
		cout << endl;
		cout << "СИНТАКСИЧЕСКИЙ АНАЛИЗ УСПЕШНО ЗАВЕРШЁН" << endl;
		cout << endl;
	}
	else {
		cout << endl;
		cout << "В СИНТАКСИЧЕСКОМ АНАЛИЗЕ ДОПУЩЕНА ОШИБКА" << endl;
		cout << endl;
		return false;
	}
	return true;
}


//Для правила D -> DLIST => “\n” [=> D]
bool Syntax::On_D(Node*& root)
{
	if (!On_DLIST(root)) return false;
	if (!On_D(root)) RollBack();
	return true;
}


//основное правило
bool Syntax::On_DLIST(Node*& root)
{
	Node* childIF = nullptr;
	Node* childPR = nullptr;
	Node* childFOR = nullptr;
	Node* childFUNC = nullptr;
	Node* ExprChild = nullptr;
	Node* childARR = nullptr;
	Node* childArrExpr = nullptr;
	SaveStatement();

	//проверка на функцию
	if (On_FUNC(childFUNC)) {
		root->next.push_back(childFUNC);
		if (On_BS(root)) {
			return true;
		}
		else {
			return false;
		}
	}

	//проверка на вывод
	if (On_PR(childPR)) {
		root->next.push_back(childPR);
		if (On_BS(root)) {
			return true;
		}
		else {
			return false;
		}
	}

	//проверка на условный оператор if
	if (On_IF(childIF)) {
		root->next.push_back(childIF);
		if (On_BS(root)) {
			return true;
		}
		else {
			return false;
		}
	}

	//проверка на цикл for
	if (On_FOR(childFOR)) {
		root->next.push_back(childFOR);
		if (On_BS(root)) {
			return true;
		}
		else {
			return false;
		}
	}

	//проверка на объявление массива
	if (On_ARR(childARR)) {
		root->next.push_back(childARR);
		if (On_BS(root)) {
			return true;
		}
		else {
			return false;
		}
	}

	//проверка на инициализацию массива
	if (On_ArrInExpr(childArrExpr)) {
		root->next.push_back(childArrExpr);
		if (On_BS(root)) {
			return true;
		}
		else {
			return false;
		}
	}

	//если не выпало ни одно из ключевых слов, то проверяем на идентификацию переменной
	if (On_Expr(ExprChild)) {
		root->next.push_back(ExprChild);
	}
	else 
		return false;
	return true;
}


//print
bool Syntax::On_PR(Node*& root)
{
	root = new Node(PRSTART, "PRSTART");
	Node* сhild = nullptr;
	bool check = false;
	SaveStatement();
	if(On_BS(root));
	if (++it >= lexList.size()) return false;
	cout << "On_Print() = ";
	PrintToken(lexList[it].GetType);
	if (lexList[it].GetType == PRINT) {
		if (On_ArrExpr(сhild, init = false)) {
			check = true;
			root->next.push_back(сhild);
		}
		else
			RollBack();
		if (On_FuncExpr(сhild)) {
			check = true;
			root->next.push_back(сhild);
		}
		else
			RollBack();
		if (On_I(сhild, init = false)) {
			check = true;
			root->next.push_back(сhild);
		}
		if (On_N(сhild)) {
			check = true;
			root->next.push_back(сhild);
		}
		if (On_STR(сhild)) {
			check = true;
			root->next.push_back(сhild);
		}
		if (check) {
			SaveStatement();
			return true;
		}
		throw SynErr("Ошибка в операторе print");
	}
	else {
		RollBack();
		return false;
	}
}


//условие функции
bool Syntax::On_FuncCond(Node*& root) {
	bool check1 = false;
	bool check2 = false;
	root = new Node(FUNCCOND, "FUNCCOND");
	Node* leftChild = nullptr;
	Node* rightChild = nullptr;
	if (On_FuncId(leftChild, init = true)) {
		if (++it >= lexList.size()) return false;
		if (lexList[it].GetType == LBR) {
			if (On_I(rightChild, init = true)) {
				check1 = true;
			}
			if (On_N(rightChild)) {
				check2 = true;
			}
			if (check1 && check2) {
				throw SynErr("Ошибка в функции. Неверно заданный аргумент.");
			}
			else if (check1 || check2) {
				if (++it >= lexList.size()) return false;
				if (lexList[it].GetType == RBR) {
					root->next.push_back(leftChild);
					root->next.push_back(rightChild);
					return true;
				}
				else throw SynErr("Ошибка в функции. Нет закрывающейся скобки.");
			}
			else throw SynErr("Ошибка в функции. Неверно заданный аргумент.");
		}
		else throw SynErr("Ошибка в функции. Нет открывающейся скобки.");
	}
}


//function
bool Syntax::On_FUNC(Node*& root) {
	Node* condChild = new Node(FUNCCOND, "FUNCCOND");
	Node* bodyChild = new Node(FUNCBODY, "FUNCBODY");
	bool check = false;
	SaveStatement();
	if (On_BS(root)) ;
	if (++it >= lexList.size()) return false;
	cout << "On_FUNCTION() = ";
	PrintToken(lexList[it].GetType);
	if (lexList[it].GetType == FUNCTION) {
		root = new Node(FUNCSTART,"FUNCSTART");
		if (On_FuncCond(condChild)) {
			root->next.push_back(condChild);
			if (!On_BS(root))
				throw SynErr("Ошибка в функции. Нет переноса строки.");
			if (!On_D(bodyChild))
				throw SynErr("Ошибка в теле функции.");
			else
				root->next.push_back(bodyChild);
			if (++it >= lexList.size()) return false;
			if (lexList[it].GetType == END) {
				if (++it >= lexList.size()) return false;
				cout << "On_FUNCTION_END() = ";
				PrintToken(lexList[it].GetType);
				if (lexList[it].GetType == FUNCTION) {
					SaveStatement();
					return true;
				}
				else throw SynErr("Ошибка в функции. Нет ключевого слова function в конце функции.");
			}
			else throw SynErr("Ошибка в функции. Нет ключевого слова end в конце функции.");
		}
		else throw SynErr("Ошибка в функции. Ошибка в объявлении функции.");
	}
	else {
		RollBack();
		return false;
	}
}


//выражение
bool Syntax::On_Expr(Node*& root) {
	Node* leftNode = nullptr;
	Node* rightNode = nullptr;
	if (On_I(leftNode, init = true)) {
		if (++it >= lexList.size()) return false;
		cout << "On_Expr() = ";
		PrintToken(lexList[it].GetType);
		if (lexList[it].GetType == EQUAL) {
			root = new Node(EQUAL, "EQUAL");
			if (!On_Result(rightNode)) {
				return false;
			}
			else {
				root->next.push_back(leftNode);
				root->next.push_back(rightNode);
				return true;
			}
		}
		else throw SynErr("Ошибка в выражении. Нет оператора равенства.");
	}
	else {
		return false;
	}
}


//объявление
bool Syntax::On_Declar(Node*& root) {
	Node* leftNode = nullptr;
	Node* rightNode = nullptr;
	root = new Node(DECL, "DECL");
	if (On_I(leftNode, init = true)) {
		if (++it >= lexList.size()) return false;
		if (lexList[it].GetType == EQUAL) {
			if (On_N(rightNode)) {
				root = new Node(EQUAL, "=");
				root->next.push_back(leftNode);
				root->next.push_back(rightNode);
				return true;
			}
			else throw SynErr("Ошибка в условии цикла. Не задан диапазон.");
		}
		else throw SynErr("Ошибка в условии цикла. Нет оператора равенства.");
	}
	else {
		return false;
	}
}


//цикл for
bool Syntax::On_FOR(Node*& root) {
	Node* declarChild = nullptr;
	Node* numChild = nullptr;
	Node* bodyChild = nullptr;
	Node* nextIdChild = nullptr;
	SaveStatement();
	if (On_BS(root));
	if (++it >= lexList.size()) return false;
	cout << "On_FOR() = ";
	PrintToken(lexList[it].GetType);
	if (lexList[it].GetType == FOR) {
		root = new Node(FORSTART, "FORSTART");
		if(On_Declar(declarChild)){
			root->next.push_back(declarChild);
			if (++it >= lexList.size()) return false;
			if (lexList[it].GetType == TO) {
				if (On_N(numChild)) {
					root->next.push_back(numChild);
					if (!On_BS(root))
						throw SynErr("Ошибка в цикле for. Нет переноса строки.");
					bodyChild = new Node(FORBODY, "FORBODY");
					if (!On_D(bodyChild))
						throw SynErr("Ошибка в теле цикла for.");
					else
						root->next.push_back(bodyChild);
				}
				if (++it >= lexList.size()) return false;
				if (lexList[it].GetType == NEXT) {
					nextIdChild = new Node(FORNEXT, "FORNEXT");
					if (On_I(nextIdChild, init = false)) {
					root->next.push_back(nextIdChild);
						if (!On_BS(root))
							throw SynErr("Ошибка в цикле for. Нет переноса строки.");
					}
				}
				else throw SynErr("Ошибка в цикле for. Нет ключевого слова next.");
				if (++it >= lexList.size()) return false;
				cout << "On_FOR_end() = ";
				PrintToken(lexList[it].GetType);
				if (lexList[it].GetType == END) {
					SaveStatement();
					return true;
				}
				else throw SynErr("Ошибка в цикле for. Нет ключевого слова end.");
			}
			else throw SynErr("Ошибка в цикле for. Нет ключевого слова to.");
		}
		else throw SynErr("Ошибка в условии цикла for.");
	}
	else {
		RollBack();
		return false;
	}
}


//условие если
bool Syntax::On_IFCond(Node*& root) {
	bool check = false;
	bool check1 = false;
	bool check2 = false;
	bool check3 = false;
	Node* leftChild = nullptr;
	Node* rightChild = nullptr;
	if (On_I(leftChild, init = false)) {
		check = true;
	}
	if (On_N(leftChild)) {
		check1 = true;
	}
	if (check && check1) {
		throw SynErr("Ошибка в условии if.");
	}
	else if (check || check1) {
		if (On_CO(root)) {
			if (On_I(rightChild, init = false)) {
				check2 = true;
			}
			if (On_N(rightChild)) {
				check3 = true;
			}
			if (check2 && check3) {
				throw SynErr("Ошибка в условии if.");
			}
			else if (check2 || check3) {
				root->next.push_back(leftChild);
				root->next.push_back(rightChild);
				return true;
			}
			else
				throw SynErr("Ошибка в условии if.");
		}
	}
	else
		throw SynErr("Ошибка в условии if.");
}


//условие иначе
bool Syntax::On_IFCondElse(Node*& root) {
	if (++it >= lexList.size()) return false;
	cout << "On_IFCondElse() = ";
	PrintToken(lexList[it].GetType);
	if (lexList[it].GetType == ELSE) {
		if (!On_BS(root))
			throw SynErr("Ошибка в операторе else");
		if (!On_D(root))
			throw SynErr("Ошибка в теле оператора else");
	}
	else {
		RollBack();
	}
}


//условный оператор If
bool Syntax::On_IF(Node*& root) {
	Node* condChild = new Node(IFCN, "IFCN");
	Node* bodyChild = new Node(IFBODY, "IFBODY");
	Node* elseChild = new Node(IFELSE, "IFELSE");
	SaveStatement();
	if(On_BS(root));
	if (++it >= lexList.size()) return false;
	cout << "On_IF() = ";
	PrintToken(lexList[it].GetType);
	if (lexList[it].GetType == IF) {
		root = new Node(IFSTART,"IFSTART");
		root->next.push_back(condChild);
		SaveStatement();
		if(On_IFCond(condChild)){
			root->next.push_back(condChild);
			if (++it >= lexList.size()) return false;
			if (lexList[it].GetType == THEN) {
				if (!On_BS(root))
					throw SynErr("Ошибка в операторе if");
				if (!On_D(bodyChild))
					throw SynErr("Ошибка в операторе if");
				else
					root->next.push_back(bodyChild);
				if (On_IFCondElse(elseChild)) root->next.push_back(elseChild);;
				if (++it >= lexList.size()) return false;
				if (lexList[it].GetType == END) {
					if (++it >= lexList.size()) return false;
					if (lexList[it].GetType == IF) {
						SaveStatement();
						cout << "On_IF_END() = ";
						PrintToken(lexList[it].GetType);
						return true;
					}
					else throw SynErr("Ошибка в операторе if. Нет ключевого слова if в конце оператора.");
				}
				else throw SynErr("Ошибка в операторе if. Нет ключевого слова end.");
			}
			else throw SynErr("Ошибка в операторе if. Нет ключевого слова then.");
		}
		else throw SynErr("Ошибка в условии оператора if.");
	}
	else {
		RollBack();
		return false;
	}
}


//проверка на равенство
bool Syntax::On_CO(Node*& root)
{
	SaveStatement();
	if (++it >= lexList.size()) return false;
	cout << "On_CO() = ";
	PrintToken(lexList[it].GetType);
	if (lexList[it].GetType == MTHAN) {
		SaveStatement();
		if (++it >= lexList.size()) return false;
		if (lexList[it].GetType == ID || lexList[it].GetType == DIGIT) {
			RollBack();
			root = new Node(MTHANCOMP, "MTHANCOMP");
			return true;
		}
		else {
			throw SynErr("Ошибка в сравнении. Неверно задан знак больше.");
		}
	}
	else if (lexList[it].GetType == LTHAN) {
		SaveStatement();
		if (++it >= lexList.size()) return false;
		if (lexList[it].GetType == ID || lexList[it].GetType == DIGIT) {
			RollBack();
			root = new Node(LTHANCOMP, "LTHANCOMP");
			return true;
		}
		else {
			throw SynErr("Ошибка в сравнении. Неверно задан знак меньше.");
		}
	}
	else if (lexList[it].GetType == EQUAL) {
		SaveStatement();
		if (++it >= lexList.size()) return false;
		if (lexList[it].GetType == ID || lexList[it].GetType == DIGIT) {
			RollBack();
			root = new Node(EQUAL, "EQUAL");
			return true;
		}
		else {
			throw SynErr("Ошибка в сравнении. Неверно задан знак равенства.");
		}
	}
	else if (lexList[it].GetType == MTHAN_EQUAL) {
		SaveStatement();
		if (++it >= lexList.size()) return false;
		if (lexList[it].GetType == ID || lexList[it].GetType == DIGIT) {
			RollBack();
			root = new Node(MTHAN_EQUAT, "MTHAN_EQUAT");
			return true;
		}
		else {
			throw SynErr("Ошибка в сравнении. Неверно задан знак больше или равно.");
		}
	}
	else if (lexList[it].GetType == LTHAN_EQUAL) {
		SaveStatement();
		if (++it >= lexList.size()) return false;
		if (lexList[it].GetType == ID || lexList[it].GetType == DIGIT) {
			RollBack();
			root = new Node(LTHAN_EQUAT, "LTHAN_EQUAT");
			return true;
		}
		else {
			throw SynErr("Ошибка в сравнении. Неверно задан знак меньше или равно.");
		}
	}
	else {
		throw SynErr("Ошибка в сравнении. Неизвестный оператор сравнения.");
	}
}


//проверка на конец строки
bool Syntax::On_BS(Node*& root) {
	SaveStatement();
	if (++it >= lexList.size()) return false;
	cout << "On_BS() = ";
	PrintToken(lexList[it].GetType);
	if (lexList[it].GetType == BSLASH) {
		SaveStatement();
		return true;
	}
	else { 
		RollBack(); 
	}
}


//вызов Эдд
bool Syntax::On_Result(Node*& root)
{
	if (On_Add(root))
		return true;
	else
		return false;
}


//плюс/минус переход в Мулт
bool Syntax::On_Add(Node*& root)
{
	Node* leftChild = nullptr;
	Node* rightChild = nullptr;
	Node* tmpRoot = nullptr;
	if (!On_Mult(leftChild))
		return false;
	SaveStatement();
	if (++it >= lexList.size()) return false;
	cout << "On_Add() = ";
	PrintToken(lexList[it].GetType);
	while (lexList[it].GetType == PLUS || lexList[it].GetType == MINUS) {
		if (lexList[it].GetType == PLUS) {
			tmpRoot = new Node(PLUS, lexList[it]._value);
			tmpRoot->data.n_type = NType::PLUSS;
		}
		else if (lexList[it].GetType == MINUS) {
			tmpRoot = new Node(MINUS, lexList[it]._value);
			tmpRoot->data.n_type = NType::MIN;
		}
		if (!On_Mult(rightChild))
			return false;
		if (root == nullptr)
			tmpRoot->next.push_back(leftChild);
		else
			tmpRoot->next.push_back(root);
		tmpRoot->next.push_back(rightChild);
		root = new Node(*tmpRoot);
		if (++it >= lexList.size()) return false;
	}
	RollBack();
	if (root == nullptr)
		root = leftChild;
	return true;
}


//умножение/деление переход в Группу
bool Syntax::On_Mult(Node*& root)
{
	Node* leftChild = nullptr;
	Node* rightChild = nullptr;
	Node* tmpRoot = nullptr;

	if (!On_Group(leftChild))
		return false;
	SaveStatement();
	if (++it >= lexList.size()) return false;
	cout << "On_Mult() = ";
	PrintToken(lexList[it].GetType);
	while (lexList[it].GetType == MUL || lexList[it].GetType == DIV) {
		if (lexList[it].GetType == MUL) {
			tmpRoot = new Node(MUL, lexList[it]._value);
			tmpRoot->data.n_type = NType::MULT;
		}
		else if (lexList[it].GetType == DIV) {
			tmpRoot = new Node(DIV, lexList[it]._value);
			tmpRoot->data.n_type = NType::DIVID;
		}

		if (!On_Group(rightChild))
			return false;
		if (root == nullptr)
			tmpRoot->next.push_back(leftChild);
		else
			tmpRoot->next.push_back(root);
		tmpRoot->next.push_back(rightChild);
		root = new Node(*tmpRoot);
		if (++it >= lexList.size()) return false;
	}
	RollBack();
	if (root == nullptr)
		root = leftChild;
	return true;
}


//выражение в скобках или число/айди/функция/квадратный корень
bool Syntax::On_Group(Node*& root)
{
	SaveStatement();
	if (++it >= lexList.size()) return false;
	cout << "On_Group() = ";
	PrintToken(lexList[it].GetType);
	if (lexList[it].GetType == LBR) {
		if(!On_Add(root)) return false;
		if (++it >= lexList.size()) return false;
		if (lexList[it].GetType == RBR) {
			SaveStatement();
			return true;
		}
		else 
			throw SynErr("Ошибка в количестве скобок.");
	}
	else
		RollBack();
	if (On_FuncExpr(root)) {
		return true;
	}
	else if (On_I(root, init = false)) {
		return true;
	}
	else if (On_N(root)) {
		return true;
	}
	else if (On_MinNI(root)) {
		return true;
	}
	else if (On_SQR(root)) {
		return true;
	}
	throw SynErr("Неизвестный оператор.");
	return false;
}


//число
bool Syntax::On_N(Node*& root)
{
	if (++it >= lexList.size()) return false;
	cout << "On_N() = ";
	PrintToken(lexList[it].GetType);
	if (lexList[it].GetType != DIGIT) {
		RollBack();
		return false;
	}
	root = new Node(DIGIT, lexList[it]._value);
	root->data.n_type = NType::NUMBER;
	SaveStatement();
	return true;
}


//минус перед идентификатором или числом
bool Syntax::On_MinNI(Node*& root)
{
	Node* child = nullptr;
	if (++it >= lexList.size()) return false;
	cout << "On_MinNI() = ";
	PrintToken(lexList[it].GetType);
	if (lexList[it].GetType == MINUS) {
		SaveStatement();
		root = new Node(MINUS, lexList[it]._value);
		root->data.n_type = NType::UMIN;
			if (On_N(child)){
				SaveStatement();
				root->next.push_back(child);
				return true;		
			}	
			else if (On_I(child, init = false)) {
				SaveStatement();
				root->next.push_back(child);
				return true;
			}
	}
	RollBack();
	if (On_N(root)) {
		return true;
	}
	if (On_I(root,init = false)) {
		return true;
	}
	return false;
}


//идентификатор
bool Syntax::On_I(Node*& root, bool init)
{
	bool flag = false;
	if (++it >= lexList.size()) return false;
	cout << "On_I() = ";
	PrintToken(lexList[it].GetType);
	if (lexList[it].GetType != ID) {
		RollBack();
		return false;
	}
	SaveStatement();
	root = new Node(ID, lexList[it]._value);
	root->data.n_type = NType::INDEF;

	if (IdTable.pushVarID(root->data.value,init)) {
		return true;
	}
	else {
		throw SynErr("Семантическая ошибка. Необъявленная переменная.");
		return false;
	}
}



//имя функции
bool Syntax::On_FuncId(Node*& root, bool init)
{
	SaveStatement();
	if (++it >= lexList.size()) return false;
	cout << "On_FuncId() = ";
	PrintToken(lexList[it].GetType);
	if (lexList[it].GetType != ID) {
		RollBack();
		return false;
	}
	if (++it >= lexList.size()) return false;
	if (lexList[it].GetType != LBR) {
		RollBack();
		return false;
	}
	RollBack();
	if (++it >= lexList.size()) return false;
	SaveStatement();
	root = new Node(ID, lexList[it]._value);
	root->data.n_type = NType::FUNCID;

	if (IdTable.pushFuncID(root->data.value, init)) {
		return true;
	}
	else {
		throw SynErr("Семантическая ошибка. Необъявленная переменная.");
		return false;
	}
}


//квадратный корень
bool Syntax::On_SQR(Node*& root)
{
	bool check1 = false;
	bool check2 = false;
	Node* child = nullptr;
	if (++it >= lexList.size()) return false;
	cout << "On_SQR() = ";
	PrintToken(lexList[it].GetType);
	if (lexList[it].GetType == SQR) {
		SaveStatement();
		root = new Node(SQR,  lexList[it]._value);
		root->data.n_type = NType::SQRT;
		if (++it >= lexList.size()) return false;
		if (lexList[it].GetType == LBR) {
			SaveStatement();
			if (On_I(child, init = false)) {
				check1 = true;
			}
			if (On_N(child)) {
				check2 = true;
			}
			if (check1 && check2) {
				throw SynErr("Ошибка в квадратном корне. Неверный аргумент.");
			}
			else if (check1 || check2) {
				root->next.push_back(child);
				if (++it >= lexList.size()) return false;
				if (lexList[it].GetType == RBR) {
					SaveStatement();
					return true;
				}
				else {
					throw SynErr("Ошибка в квадратном корне. Нет закрывающейся скобки.");
				}
			}
			else {
				throw SynErr("Ошибка в квадратном корне. Неверный аргумент.");
			}
		}
		else {
			throw SynErr("Ошибка в квадратном корне. Нет открывающейся скобки.");
		}
		
	}
	RollBack();
	return false;
}


//вызов функции
bool Syntax::On_FuncExpr(Node*& root)
{
	Node* child = nullptr;
	if (On_FuncId(root, init = false)) {
		if (++it >= lexList.size()) return false;
		if (lexList[it].GetType == LBR) {
			cout << "On_FuncExpr() = ";
			PrintToken(lexList[it].GetType);
			if (On_Add(child));
			else
				throw SynErr("Ошибка в вызове функции. Не верно задан аргумент.");
			SaveStatement();
			root->next.push_back(child);
			if (++it >= lexList.size()) return false;
			if (lexList[it].GetType == RBR) {
				SaveStatement();
				return true;
			}
			else
				throw SynErr("Ошибка в вызове функции. Нет закрывающейся скобки.");
		}
		RollBack();
		return true;
	}
	return false;
}


//строка
bool Syntax::On_STR(Node*& root)
{
	if (++it >= lexList.size()) return false;
	cout << "On_STR() = ";
	PrintToken(lexList[it].GetType);
	if (lexList[it].GetType != STR) {
		RollBack();
		return false;
	}
	SaveStatement();
	root = new Node(STRIN, lexList[it]._value);
	return true;
}


//массив
bool Syntax::On_ARR(Node*& root) {
	bool check = false;
	SaveStatement();
	if (On_BS(root));
	if (++it >= lexList.size()) return false;
	cout << "On_ARR() = ";
	PrintToken(lexList[it].GetType);
	if (lexList[it].GetType == DIM) {
		On_ArrDec(root);
	}
	else {
		RollBack();
		return false;
	}
}


//объявление массива
bool Syntax::On_ArrDec(Node*& root) {
	bool check1 = false;
	bool check2 = false;
	root = new Node(MAS, "MAS");
	Node* leftChild = nullptr;
	Node* rightChild = nullptr;
	if (On_ArrId(leftChild, init = true)) {
		if (++it >= lexList.size()) return false;
		cout << "On_ArrDec() = ";
		PrintToken(lexList[it].GetType);
		if (lexList[it].GetType == LBR) {
			if (On_N(rightChild)) {
				check1 = true;
			}
			if (On_I(rightChild, init = true)) {
				check2 = true;
			}
			if (check1 && check2) {
				throw SynErr("Ошибка в объявлении массива. Не правильно указан размер.");
			}
			else if (check1 || check2) {
				if (++it >= lexList.size()) return false;
				if (lexList[it].GetType == RBR) {
					root->next.push_back(leftChild);
					root->next.push_back(rightChild);
					return true;
				}
				else throw SynErr("Ошибка в объявлении массива. Нет закрывающейся скобки.");
			}
			else throw SynErr("Ошибка в объявлении массива. Не правильно указан размер.");
		}
		else throw SynErr("Ошибка в объявлении массива. Нет открывающейся скобки.");
	}
}


//имя массива
bool Syntax::On_ArrId(Node*& root, bool init)
{
	SaveStatement();
	if (++it >= lexList.size()) return false;
	cout << "On_ArrId() = ";
	PrintToken(lexList[it].GetType);
	if (lexList[it].GetType != ID) {
		RollBack();
		return false;
	}
	SaveStatement();
	root = new Node(ID, lexList[it]._value);
	root->data.n_type = NType::ARRID;

	if (IdTable.pushArrayID(root->data.value, init)) {
		return true;
	}
	else {
		throw SynErr("Семантическая ошибка. Необъявленная переменная массива.");
		return false;
	}
}


//инициализация массива
bool Syntax::On_ArrExpr(Node*& root, bool init)
{
	Node* rightChild = nullptr;
	Node* leftChild = nullptr;
	
	if (On_FindArrId(leftChild, init = false)) {
		if (++it >= lexList.size()) return false;
		if (lexList[it].GetType == KLBR) {
			cout << "On_ArrExpr() = ";
			PrintToken(lexList[it].GetType);
			if (On_Add(rightChild));
			SaveStatement();
			root = new Node(ARRID, "ARRID");
			root->next.push_back(leftChild);
			root->next.push_back(rightChild);
			if (++it >= lexList.size()) return false;
			PrintToken(lexList[it].GetType);
			if (lexList[it].GetType == KRBR) {
				SaveStatement();
				return true;
			}
			else
				throw SynErr("Ошибка в вызове массива. Нет закрывающейся квадратной скобки.");
		}
		RollBack();
		return true;
	}

	return false;
}


//вызов массива
bool Syntax::On_ArrInExpr(Node*& root) {
	Node* leftNode = nullptr;
	Node* rightNode = nullptr;
	if (On_ArrExpr(leftNode, init = true)) {
		if (++it >= lexList.size()) return false;
		cout << "On_ArrInExpr() = ";
		PrintToken(lexList[it].GetType);
		if (lexList[it].GetType == EQUAL) {
			root = new Node(EQUAL, lexList[it]._value);
			if (!On_Result(rightNode)) {
				return false;
			}
			else {
				root->next.push_back(leftNode);
				root->next.push_back(rightNode);
				return true;
			}
		}
		else throw SynErr("Ошибка в инициализации массива");
	}
	else {
		return false;
	}
}


//имя массива
bool Syntax::On_FindArrId(Node*& root, bool init)
{
	SaveStatement();
	if (++it >= lexList.size()) return false;
	cout << "On_FindArrId() = ";
	PrintToken(lexList[it].GetType);
	if (lexList[it].GetType != ID) {
		RollBack();
		return false;
	}
	if (++it >= lexList.size()) return false;
	if (lexList[it].GetType != KLBR) {
		RollBack();
		return false;
	}
	RollBack();
	if (++it >= lexList.size()) return false;
	SaveStatement();
	root = new Node(ID, lexList[it]._value);
	root->data.n_type = NType::ARRID;

	if (IdTable.pushArrayID(root->data.value, init)) {
		return true;
	}
	else {
		throw SynErr("Семантическая ошибка. Необъявленная переменная массива.");
		return false;
	}
}