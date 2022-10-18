#pragma once
#include <array>
#include "Approach.h"
#include <string>
#include <iostream>
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
	virtual void run(std::array<int, 21 >* input, const std::string* setName);
protected:
	int determine_order(std::array<int, 21 >* input, int* constantDifference);
	result derive_function(const int* order, std::array<int, 21 >* input, const int* constantDifference, const std::string* setName);
	void setup_equations(std::array<std::array<Equation, 5>, 5>* equations, const int* order, const std::array<int, 21>* input);
	void setup_coeffs(const int* order, const int* firstCoeff, int* terms);
	//Equation operator-(const Equation lhs, const Equation rhs);
};

