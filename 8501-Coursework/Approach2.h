#pragma once
#include "Approach.h"
#include <iostream>
class Approach2 : public Approach {
public:
	struct resultExperimental {
		float a; //x^4
		float b; //x^3
		float c; //x^2
		float d; //x
		float e; //constant
	};
	virtual result run(std::vector<int>* input) override;
	resultExperimental run_experimental(std::vector<int>* input, const float* xOffset);
	static void display_result_experimental(const resultExperimental* result);
protected:
	
	void calculate_order_and_lead_coeff(const std::vector<int>* input, int* order, int* leadCoeff);
	void calculate_order_and_lead_coeff_experimental(const std::vector<float>* input, int* order, float* leadCoeff);

	void calculate_remaining_coeffs(int* terms, const int* highorder, std::vector<int>* set);
	void calculate_remaining_coeffs_experimental(float* terms, const int* highorder, std::vector<float>* set, const float* xOffset);
	
	float factorial_experimental(float num);
};