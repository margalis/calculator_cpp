#include "Calculator.hpp"
#include <iostream>

int
main()
{
	Calculator::welcomeInstructions();
	std::cout << "\t= " << Calculator::calculate(Calculator::inputEquation());
	return 0;
}
