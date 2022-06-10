#include "Calculator.hpp"
#include <iostream>
#include <vector>
#include <string>
int
main()
{
	Calculator::welcomeInstructions();

	std::cout << "\t= " << Calculator::calculate(Calculator::inputEquation());

	return 0;
}
