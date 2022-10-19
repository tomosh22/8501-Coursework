#pragma once
#include <array>
#include <string>
#include <vector>
namespace Approach2Namespace {
	struct result {
		int a; //x^4
		int b; //x^3
		int c; //x^2
		int d; //x
		int e; //constant
	};
	result run(const std::vector<int>* input, const std::string* setName);
	int factorial(int num);
	void set_order_and_lead_coeff(const int* input, int* order, int* leadCoeff);
}