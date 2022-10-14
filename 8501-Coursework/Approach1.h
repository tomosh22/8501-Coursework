#pragma once
#include "Sets.h"
namespace Approach1 {
	struct Equation;
	struct result {
		int a; //x^4
		int b; //x^3
		int c; //x^2
		int d; //x
		int e; //constant
	};
	result run(const int* input);
	int factorial(int num);
	int determine_order(const int* input, int* constantDifference);
	result derive_function(const int* order, const int* input, const int* constantDifference);
}