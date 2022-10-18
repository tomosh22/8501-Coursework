#pragma once
#include "Approach.h"
#include <iostream>
class Approach2 : public Approach {
public:
	virtual result run(const std::array<int, 21 >* input, const std::string* setName);
protected:
	void calculate_order_and_lead_coeff(const int* input, int* order, int* leadCoeff);
	void calculate_remaining_coeffs(int* terms, const int* highorder, int* set);
	
	
};