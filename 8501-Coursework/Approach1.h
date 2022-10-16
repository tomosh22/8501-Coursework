#pragma once
#include "Sets.h"
#include <array>
namespace Approach1 {
	struct Equation;
	struct result {
		int a; //x^4
		int b; //x^3
		int c; //x^2
		int d; //x
		int e; //constant
	};
	result run(std::array<int, 21 > *input);
	int factorial(int num);
	int determine_order(std::array<int, 21 >* input, int* constantDifference);
	result derive_function(const int* order, std::array<int, 21 >* input, const int* constantDifference);
}