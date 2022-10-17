#pragma once
#include <array>
#include <string>
namespace Approach2 {
	struct result {
		int a; //x^4
		int b; //x^3
		int c; //x^2
		int d; //x
		int e; //constant
	};
	result run(const std::array<int, 21 >* input, const std::string* setName);
	int factorial(int num);
	void set_order_and_lead_coeff(const int* input, int* order, int* leadCoeff);
}