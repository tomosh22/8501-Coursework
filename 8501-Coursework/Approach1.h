#pragma once
#include "Sets.h"
#include <array>
#include <string>
namespace Approach1 {
	struct Equation {
		int y; //from input
		int a; //x^4
		int b; //x^3
		int c; //x^2
		int d; //x
		int e; //constant
	};
	struct result {
		int a; //x^4
		int b; //x^3
		int c; //x^2
		int d; //x
		int e; //constant
	};
	Equation operator-(const Equation lhs, const Equation rhs);
	void run(std::array<int, 21 > *input, const std::string* setName);
	int factorial(int num);
	int determine_order(std::array<int, 21 >* input, int* constantDifference);
	result derive_function(const int* order, std::array<int, 21 >* input, const int* constantDifference, const std::string* setName);
}