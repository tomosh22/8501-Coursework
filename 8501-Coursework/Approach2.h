#pragma once
#include "Approach.h"
#include <iostream>
class Approach2 : Approach {
public:
	virtual result run(const std::array<int, 21 >* input, const std::string* setName);
protected:
	void set_order_and_lead_coeff(const int* input, int* order, int* leadCoeff);
};