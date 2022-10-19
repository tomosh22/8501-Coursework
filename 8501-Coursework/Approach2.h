#pragma once
#include "Approach.h"
#include <iostream>
class Approach2 : public Approach {
public:
	result run(std::array<int, 21 >* input, const std::string* setName);
	result run_experimental(std::array<int, 21 >* input, const std::string* setName, const int* xOffset);
protected:
	void calculate_order_and_lead_coeff(const int* input, int* order, int* leadCoeff);
	void calculate_remaining_coeffs(int* terms, const int* highorder, int* set);
	void calculate_remaining_coeffs_experimental(int* terms, const int* highorder, int* set, const int* xOffset);
	
	
};