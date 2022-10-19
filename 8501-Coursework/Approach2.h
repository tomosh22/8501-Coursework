#pragma once
#include "Approach.h"
#include <iostream>
class Approach2 : public Approach {
public:
	result run(std::vector<int>* input, const std::string* setName);
	result run_experimental(std::vector<int>* input, const std::string* setName, const int* xOffset);
protected:
	void calculate_order_and_lead_coeff(const std::vector<int>* input, int* order, int* leadCoeff);
	void calculate_remaining_coeffs(int* terms, const int* highorder, std::vector<int>* set);
	void calculate_remaining_coeffs_experimental(int* terms, const int* highorder, std::vector<int>* set, const int* xOffset);
	
	
};