#pragma once
#include "Sets.h"
namespace Approach1 {
	struct Equation;
	struct result;
	void run();
	int factorial(int num);
	int determine_order(int* input, int* constantDifference);
	Equation derive_function(const int* order, const int* input, const int* constantDifference);
}