//#include <iostream>
//#include "Token.h"
//#include "List.h"
//#include "LogicComponent.h"
//using namespace std;
//
//Token* createToken(char* char_op, int& char_op_count) {
//	int size = 2;
//	char* symbols = new char[size];
//
//	if (strcmp(char_op, "MIN") == 0)
//	{
//		symbols[0] = '<';
//		symbols[1] = '\0';
//	}
//	else if (strcmp(char_op, "MAX") == 0)
//	{
//		symbols[0] = '>';
//		symbols[1] = '\0';
//	}
//	else if (strcmp(char_op, "IF") == 0) {
//		symbols[0] = '?';
//		symbols[1] = '\0';
//	}
//	else if (strcmp(char_op, "N") == 0) {
//		symbols[0] = '~';
//		symbols[1] = '\0';
//	}
//	else {
//		delete[] symbols;
//		size = char_op_count;
//		symbols = new char[size];
//		for (int i = 0; i < size; i++) {
//			symbols[i] = char_op[i];
//		}
//	}
//
//
//	Token* temp = new Token(symbols, size);
//	for (int i = 0; i < char_op_count; i++) {
//		char_op[i] = -52; // default undefined value for char
//	}
//	char_op_count = 0;
//	delete[] symbols;
//	return temp;
//}
//
//void pullOutOperator(Token* end, List& outputList, List& stack, LogicComponent& logic) {
//	while (end != nullptr && end->symbols[0] != '(') {
//		outputList.push_back(end);
//		stack.pop_back();
//		end = stack.end();
//	}
//	if (end != nullptr && end->symbols[0] == '(') {
//		stack.pop_back();
//		end = stack.end();
//	}
//	if (end != nullptr) {
//		short int prior = logic.findPriority(end->symbols[0]);
//		if (prior == 3 && end->symbols[0] != '~') {
//			outputList.push_back(end);
//			stack.pop_back();
//			end = stack.end();
//		}
//	}
//}
//
//void replaceOperations(Token* token, List& outputList, List& stack, LogicComponent& logic) {
//	Token* tmp = stack.end();
//	int tokenPrior = logic.findPriority(token->symbols[0]);
//	int stackPrior = -1;
//	if (tmp != nullptr) {
//		stackPrior = logic.findPriority(tmp->symbols[0]);
//	}
//
//	while (tmp != nullptr && stackPrior != -1 && stackPrior <= 3 && stackPrior >= tokenPrior) {
//		if (tokenPrior != -1) {
//			if (token->symbols[0] != '~') {
//				outputList.push_back(tmp);
//				stack.pop_back();
//				tmp = stack.end();
//				if (tmp != nullptr) {
//					stackPrior = logic.findPriority(tmp->symbols[0]);
//				}
//				else stackPrior = -1;
//			}
//			else break;
//		}
//	}
//	stack.push_back(token);
//}
//
//
////Token* convertToONP(Token* token, bool callFromConvert,
////	bool isInsideFunction, short int* counter_operands = nullptr) {
////	Token* functionPointer = nullptr;
////	short int functionArgs = 0;
////
////}
////Token* token, bool callFromConvert,
////bool isInsideFunction, short int* counter_operands = nullptr,
//Token* convertToONP(Token* token, bool callFromConvert,
//	bool isInsideFunction, short int* counter_operands,
//	char* input, char* char_op, int& char_op_count, int& c,
//	List& outputList, List& stack, LogicComponent& logic) {
//	Token* functionPointer = nullptr;
//	short int functionArgs = 0;
//	while (input[c] != '\0') {
//		if (input[c] != ' ') {
//			if (input[c] == '.') {
//				pullOutOperator(stack.end(), outputList, stack, logic);
//				outputList.drawList();
//			}
//			else char_op[char_op_count++] = input[c];
//		}
//		else if (input[c] == '\n') {
//		}
//		else {
//			//token_count++;
//			char_op[char_op_count++] = '\0';
//			Token* tm = (token == nullptr) ? createToken(char_op, char_op_count) : new Token(*token);
//
//			if (char_op[0] != '\0' && logic.isNumber(tm->symbols)) {
//				outputList.push_back(tm);
//			}
//			else {
//				switch (tm->symbols[0]) {
//				case '+': case '-':
//				case '*': case '/':
//				case '~':
//					replaceOperations(tm, outputList, stack, logic);
//					break;
//					// functions
//				case '?': case '<':
//				case '>':
//					//stack.push_back(tm);
//					functionPointer = new Token(*tm);
//					functionArgs = 0;
//					//functionPointer = new Token(createToken(char_op, char_op_count));
//					//functionArgs = 0;
//					break;
//					// brackets
//				case '(':
//				{
//					stack.push_back(tm);
//					tm = convertToONP(nullptr, true,
//						functionPointer != nullptr, &functionArgs, input,
//						char_op, char_op_count,
//						++c, outputList, stack, logic);
//					//if (!isERROR) {
//						cout << "stack in token: ";
//						stack.drawList();
//						cout << "outputlist in token: ";
//						outputList.drawList();
//						if (functionPointer) {
//							functionPointer->arguments = functionArgs;
//							stack.push_back(functionPointer);
//							cout << "stack in token2: ";
//							stack.drawList();
//							cout << "outputlist in token2: ";
//							outputList.drawList();
//
//						/*	auto* end = stack.end();
//							if (end != nullptr) {
//								int prior = logic.findPriority(end->symbols[0]);
//								if (prior == 3) {
//									outputList.push_back(end);
//									stack.pop_back();
//									end = stack.end();
//								}
//							}*/
//							delete functionPointer;
//						}
//						functionPointer = nullptr;
//
//					//else return nullptr;
//					break;
//				}
//				case ',':
//				{
//					if (isInsideFunction && counter_operands) {
//						auto* end = stack.end();
//						while (end != nullptr && end->symbols[0] != '(') {
//							outputList.push_back(end);
//							stack.pop_back();
//							end = stack.end();
//						}
//						*counter_operands += 1;
//						cout << "\nstack in if: ";
//						stack.drawList(); printf("\n");
//						cout << "outputList in if:\n";
//						outputList.drawList(); printf("\n");
//					}
//					break;
//				}
//				case ')': {
//					pullOutOperator(stack.end(), outputList, stack, logic);
//					if (isInsideFunction && counter_operands) *counter_operands += 1;
//					if (callFromConvert) return tm; 
//					break;
//				}
//
//
//				default:break;
//				}
//				cout << "\nstack: ";
//				stack.drawList(); printf("\n");
//				cout << "outputList:\n";
//				outputList.drawList(); printf("\n");
//			}
//			if (tm != nullptr && tm->symbols[0] != ')') delete tm; 
//			// sprawdzic memory leak i jak dziala bez warunku na zamkniety nawias
//		}
//		c++;
//	}
//	return nullptr;
//}
//
//int main()
//{
//
//	LogicComponent logic;
//
//	const int EQUATION_LENGTH = 10000; // zamienic
//	//char* input = new char[EQUATION_LENGTH];
//
//	int amount_of_lines = 0;
//
//	List outputList;
//	List stack;
//	List operationList;
//	List helpList;
//
//	/*
//	* zrob cin linijki i for dla tych linijek (wiecej niz 1 linijka wejscia)
//	*
//	*/
//
//	/*
//	* Sprawdzic notacje, bo są nawiasy, chociaz nie musza byc teoretycznie
//	* Dodac funkcje min,max,if,N
//	*/
//
//
//	const short int CHAR_OP_LENGTH = 20; // 19 dlugosc int + 1
//	char char_op[CHAR_OP_LENGTH];
//	int char_op_count = 0;
//	int outputIndex = 0;
//	int c = 0;
//
//	// liczy od 0, gdzie 0 to oznacza jeden element
//	short int prev_function_count = -1; // liczy od 0, gdzie 0 to oznacza jeden element
//	int token_count = 0;
//
//	short int functionArgs = 0;
//	Token* functionPointer = nullptr;
//	char input[] = "N ( MIN ( 1 , 1 , 6 , 1 , 7 ) + N ( 8 ) ) .";//
//
//	convertToONP(nullptr, false, false, nullptr, input, char_op, char_op_count, c, outputList, stack, logic);
//
//	
//
//	printf("\n");
//	//cout << "operationList:\n";
//	//operationList.drawList();
//
//	//printf("\n");
//	//cout << "helpList:\n";
//	//helpList.drawList();
//	//cout << "\noutputList:\n";
//
//	//printf("\n");
//	//outputList.drawList(); printf("\n");
//	//auto* end = stack.end();
//	//cout << "Poza glownym while\n";
//	//while (end != nullptr) {
//	//	cout << "Cos jest: " << end->symbols[0] << endl;
//	//	outputList.push_back(end);
//	//	stack.pop_back();
//	//	end = stack.end();
//	//}
//	//printf("\n");
//	
//}
//
//
//
//
//
//
