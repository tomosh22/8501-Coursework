#pragma once
#include "Sets.h"
#include <array>
#include <string>
#include <vector>
namespace Approach1Namespace {
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
	void run(std::vector<int> *input, const std::string* setName);
	int factorial(int num);
	int determine_order(std::vector<int>* input, int* constantDifference);
	result derive_function(const int* order, std::vector<int>* input, const int* constantDifference, const std::string* setName);
}