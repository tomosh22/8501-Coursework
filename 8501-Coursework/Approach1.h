#pragma once
#include <array>
#include "Approach.h"
class Approach1 : public Approach {
public:
	struct Equation {
		int y; //from input
		int a; //x^4
		int b; //x^3
		int c; //x^2
		int d; //x
		int e; //constant
	};
	result run(std::vector<int>* input);
protected:
	int determine_order(std::vector<int>* input, int* constantDifference);
	result derive_function(const int* order, std::vector<int>* input, const int* constantDifference);
	void setup_equations(std::array<std::array<Equation, 5>, 5>* equations, const int* order, const std::vector<int>* input);
	void setup_coeffs(const int* order, const int* firstCoeff, int* terms);
	//Equation operator-(const Equation lhs, const Equation rhs);
};

