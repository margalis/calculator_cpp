#ifndef CALCULATOR_HPP
#define CALCULATOR_HPP

#include <vector>
#include <stack>
#include <string>

using VS = std::vector<std::string>;

class Calculator {
	
	static bool isValid(VS s);
	static int precedence(char currentOperator);
	static int isOperator(char currentSymbol);
	static int isNumber(std::string s);
public:
	static std::string truncateString(std::string& s);
	static VS fromStringToVector(std::string& s);
	std::string fromVectorToString(const std::vector<std::string>& v); /// can be usefull
	static double stepCalculate(std::stack<double>& numbers, std::stack<char>& operators);
public:	
	static void welcomeInstructions();
	static VS inputEquation();
	static double calculate(VS equation);
	
private:
	Calculator() = delete;
	~Calculator() = delete;
};

#endif
