#include "Approach2.h"
Approach::result Approach2::run(std::vector<int>* input) {
	int highorder = -1;
	int leadCoeff = -1;
	std::vector<int> set;
	for (int x = 0; x < input->size(); x++){
		set.push_back(input->at(x));
	}
	int terms[5]{};
	calculate_order_and_lead_coeff(&set, &highorder, &leadCoeff);
	terms[4 - highorder] = leadCoeff;
	calculate_remaining_coeffs(terms, &highorder, &set);
	result r{ terms[0],terms[1],terms[2],terms[3],terms[4] };
	return r;
}

Approach::result Approach2::run_experimental(std::vector<int>* input, const int* xOffset) {
	int highorder = -1;
	int leadCoeff = -1;
	std::vector<int> set;
	for (int x = 0; x < input->size(); x++){
		set.push_back(input->at(x));
	}
	int terms[5]{};
	calculate_order_and_lead_coeff(&set, &highorder, &leadCoeff);
	terms[4 - highorder] = leadCoeff;
	calculate_remaining_coeffs_experimental(terms, &highorder, &set, xOffset);
	result r{ terms[0],terms[1],terms[2],terms[3],terms[4] };
	return r;
}



void Approach2::calculate_order_and_lead_coeff(const std::vector<int>* input, int* order, int* leadCoeff) {
	int values[5][5]{};
	for (int x = 0; x < 5; x++){
		values[0][x] = input->at(x);
	}
	int constantDifference = 0;
	int currentOrder = 1;
	while (true) {
		for (int x = 0; x < 5 - currentOrder; x++){
			values[currentOrder][x] = values[currentOrder - 1][x + 1] - values[currentOrder - 1][x];
		}
		if (values[currentOrder][0] == values[currentOrder][1] || (currentOrder == 4)) {
			*order = currentOrder;
			*leadCoeff = values[currentOrder][0] / factorial(currentOrder);
			return;
		}
		currentOrder++;
	}
}

void Approach2::calculate_remaining_coeffs(int* terms, const int* highorder, std::vector<int>* set) {
	int values[4][4]{};
	for (int order = *highorder; order > 0; order--) {
		for (int x = 0; x < order + 1; x++) {
			set->at(x) -= terms[4 - order] * pow(x, order);
			values[0][x] = set->at(x);
		}
		for (int x = 1; x < order; x++) {
			for (int y = 0; y < 4 - x; y++) {
				values[x][y] = values[x - 1][y + 1] - values[x - 1][y];
			}
		}
		terms[5 - order] = values[order - 1][0] / factorial(order - 1);
	}
}

void Approach2::calculate_remaining_coeffs_experimental(int* terms, const int* highorder, std::vector<int>* set, const int* xOffset) {
	int values[4][4]{};
	for (int order = *highorder; order > 0; order--) {
		for (int x = 0; x < order + 1; x++) {
			set->at(x) -= terms[4 - order] * pow(x+*xOffset, order);
			values[0][x] = set->at(x);
		}
		for (int x = 1; x < order; x++) {
			for (int y = 0; y < 4 - x; y++) {
				values[x][y] = values[x - 1][y + 1] - values[x - 1][y];
			}
		}
		terms[5 - order] = values[order - 1][0] / factorial(order - 1);
	}
}