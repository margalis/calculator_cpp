#include "Calculator.hpp"

#include <iostream>
#include <cassert>
#include <stack>

void
Calculator::welcomeInstructions()
{
    std::string welcome = "Welcome to ccallccullattorr v0.0.\n"
                          "1.Write the equation without spaces inbetween the symbols.\n\n"                  
                          "Write the equation to calculate: ";
    std::cout << welcome << '\n';
}

VS
Calculator::inputEquation()
{
    std::string equation;
    getline(std::cin, equation);
    std::string t = truncateString(equation);
    return fromStringToVector(t);
}

bool 
Calculator::isValid(VS s)
{
    std::stack<std::string> parenthesis;
    for (VS::const_iterator i = s.begin(); i != s.end(); ++i) {
        std::string c = *i;
        if (!(isNumber(c) || isOperator(c[0]) || c == "(" || c == ")" || c==" ")) {
            return false;
        }
        ///4++5  ::error
        //if (isOperator(c[0]) && ((isOperator((*(i + 1))[0]))) || (isOperator((*(i - 1))[0]))) return false;
        
        if (c == "(") {
            parenthesis.push(c);
        }
        if (c == ")" ) {
            if (parenthesis.empty()) {
                return false;
            }
            parenthesis.pop();
        }
        if (c == "(" and *(i + 1) == ")" and s.size()==2) return false; // omg :D
    }
    if (!parenthesis.empty()) {
        return false;
    }
    return true;
}

int 
Calculator::precedence(char currentOperator)
{
    if (currentOperator == '+' || currentOperator == '-') {
        return 1;
    }
    if (currentOperator == '*' || currentOperator == '/' || currentOperator == '%') {
        return 2;
    }
    if (currentOperator == '^') { 
        return 3;
    }
    return -1;
}

int
Calculator::isOperator(char currentSymbol)
{
    return (currentSymbol == '+' || currentSymbol == '-' || currentSymbol == '/' || currentSymbol == '*' || currentSymbol == '^' || currentSymbol == '%');
}

int
Calculator::isNumber(std::string s)
{   
    ///
    char* end = nullptr;
    double val = strtod(s.c_str(), &end);
    return end != s.c_str() && *end == '\0' && val != HUGE_VAL;
}

std::string 
Calculator::truncateString(std::string& s)
{
    std::string s_new;
    for (unsigned int i = 0; i < s.length(); ++i) {
        if (s[i] == ')'|| s[i] == '('
            || isOperator(s[i])
            || (isdigit(s[i]) && (!isdigit(s[i + 1]) && s[i + 1] != '.'))
            )
        {
            if (isOperator(s[i]) && i > 0) {
                if ((isdigit(s[i - 1]) && isdigit(s[i + 1]))
                    || (s[i - 1] == ')' && isdigit(s[i + 1]))
                    || (s[i - 1] == ')' && s[i + 1] == '(')
                    || (isdigit(s[i - 1]) && s[i + 1] == '(')) {
                    s_new.push_back(s[i]);
                    s_new.push_back(' ');
                }
                else {
                    s_new.push_back(s[i]);
                }
            }
            else if (isOperator(s[i])  && i == 0) {
                s_new.push_back(s[i]);
            }
            else {
                s_new.push_back(s[i]);
                s_new.push_back(' ');
            }
        }
        else {
            s_new.push_back(s[i]);
        }
    }
    s_new.pop_back();
    return s_new;
}

VS 
Calculator::fromStringToVector(std::string& s)
{   
    VS result;
    std::string temp = "";
    for (int i = 0; i < s.length(); ++i) {

        if (s[i] == ' ') {
            result.push_back(temp);
            temp = "";
        }
        else {
            temp.push_back(s[i]);
        }

    }
    result.push_back(temp);
    return result;
}

std::string
Calculator::fromVectorToString(const std::vector<std::string>& v)
{
    std::string str;
    for (VS::const_iterator i = v.begin(); i != v.end(); ++i) {
        str += *i;
    }
    return str;
}

double
Calculator::stepCalculate(std::stack<double>& numbers, std::stack<char>& operators)
{
   double a, b;
    char op;
    a = numbers.top();
    numbers.pop();
    b = numbers.top();
    numbers.pop();
    op = operators.top();
    operators.pop();

    switch (op) {
    case '+':
        return a + b;
    case '-':
        return b - a;
    case '*':
        return a * b;
    case '/':
        if (a == 0) {
            /// manage es masy 
            return INFINITY;
        }
        else {
            return b / a;
        }
    case '%':
        return std::fmod(b, a);
    case '^':
        return pow(b, a);
    }
    return 0.0f;
}


/// using infix notation with two stacks for numbers and operators
double
Calculator::calculate(VS equation)
{
    if (!isValid(equation)) {
        std::cout << "Equation is invalid.";
        exit(0);
    }
    std::stack<double> numbers; 
    std::stack<char> operators;
    std::string c;
    double r, output;
    for (VS::const_iterator i = equation.begin(); i != equation.end(); ++i) {
        c = *i;
        if (isNumber(c)) {
            numbers.push(std::stod(c));
        }
        else if (c == "(") {
            operators.push(c[0]);
        }
        else if (c == ")") {
            while (operators.top() != '(') {
                r = stepCalculate(numbers, operators);
                numbers.push(r);
            }
            operators.pop();
        }
        else if (isOperator(c[0])) {
            while (!operators.empty() && precedence(c[0]) <= precedence(operators.top())){
                output = stepCalculate(numbers, operators);
                numbers.push(output);
            }
            operators.push(c[0]);
        }
        
    }
    while (!operators.empty()) {
            output = stepCalculate(numbers, operators);
            numbers.push(output);
    }
    double result = numbers.top();
    numbers.pop();
    /// empty every container 
    return result;  

}
