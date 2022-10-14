#pragma once
namespace Approach2 {
    struct result {
        int a; //x^4
        int b; //x^3
        int c; //x^2
        int d; //x
        int e; //constant
    };
	result run(const int* set);
	int factorial(int num);
	void set_order_and_lead_coeff(int* input, int* order, int* leadCoeff);
	void set_lead_coeff(int* input, int* leadCoeff);
}