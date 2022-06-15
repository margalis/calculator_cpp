#include "Calculator.hpp"
#include <iostream>
#include <vector>
#include <string>
int
main()
{
	Calculator::welcomeInstructions();
	while (true) {
		std::cout << "\t= " << Calculator::calculate(Calculator::inputEquation()) << '\n';
	}

	/// some testing
	/*std::string a;
	getline(std::cin, a);
	auto b = Calculator::truncatestring(a);
	std::vector<std::string>  v = Calculator::fromstringtovector(b);
	for (std::size_t i = 0; i < v.size(); ++i) {
		std::cout << v[i] << ",";
	}*/
	return 0;
}

//std::vector<std::string> temp = Calculator::inputEquation();
//std::cout << "\t= " << Calculator::calculate(temp) << '\n';