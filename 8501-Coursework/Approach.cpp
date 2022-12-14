#include "Approach.h"
int  Approach::factorial(int num) {
	if (num <= 1) { return 1; }
	return num * factorial(num - 1);
}

void Approach::display_result(const result* result) {
	std::cout
		<< ((bool)result->a ? (result->a < 0 ? "\0" : "+ ") + std::to_string(result->a) + "x^4 " : "\0")
		<< ((bool)result->b ? (result->b < 0 ? "\0" : "+ ") + std::to_string(result->b) + "x^3 " : "\0")
		<< ((bool)result->c ? (result->c < 0 ? "\0" : "+ ") + std::to_string(result->c) + "x^2 " : "\0")
		<< ((bool)result->d ? (result->d < 0 ? "\0" : "+ ") + std::to_string(result->d) + "x " : "\0")
		<< ((bool)result->e ? (result->e < 0 ? "\0" : "+ ") + std::to_string(result->e) : "\0")
		<< '\n';
}

std::string Approach::result_string(const result* result) {
	std::string s =((bool)result->a ? (result->a < 0 ? "\0" : "+ ") + std::to_string(result->a) + "x^4 " : "\0")
		+ ((bool)result->b ? (result->b < 0 ? "\0" : "+ ") + std::to_string(result->b) + "x^3 " : "\0")
		+ ((bool)result->c ? (result->c < 0 ? "\0" : "+ ") + std::to_string(result->c) + "x^2 " : "\0")
		+ ((bool)result->d ? (result->d < 0 ? "\0" : "+ ") + std::to_string(result->d) + "x " : "\0")
		+ ((bool)result->e ? (result->e < 0 ? "\0" : "+ ") + std::to_string(result->e) : "\0");
	return s;
}