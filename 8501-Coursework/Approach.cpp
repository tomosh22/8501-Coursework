#include "Approach.h"
int Approach::factorial(int num) {
	if (num <= 1) { return 1; }
	return num * factorial(num - 1);
}

void Approach::display_result(const std::string* setName, const int* terms) {
	std::cout << *setName << ' '
		<< ((bool)terms[0] ? (terms[0] < 0 ? "\0" : "+ ") + std::to_string(terms[0]) + "x^4 " : "\0")
		<< ((bool)terms[1] ? (terms[1] < 0 ? "\0" : "+ ") + std::to_string(terms[1]) + "x^3 " : "\0")
		<< ((bool)terms[2] ? (terms[2] < 0 ? "\0" : "+ ") + std::to_string(terms[2]) + "x^2 " : "\0")
		<< ((bool)terms[3] ? (terms[3] < 0 ? "\0" : "+ ") + std::to_string(terms[3]) + "x " : "\0")
		<< ((bool)terms[4] ? (terms[4] < 0 ? "\0" : "+ ") + std::to_string(terms[4]) : "\0")
		<< '\n';
}