#include "Approach1.h"

Approach1::Equation operator - (const Approach1::Equation lhs, const Approach1::Equation rhs) {
	Approach1::Equation result;
	result.y = lhs.y - rhs.y;
	result.a = lhs.a - rhs.a;
	result.b = lhs.b - rhs.b;
	result.c = lhs.c - rhs.c;
	result.d = lhs.d - rhs.d;
	result.e = lhs.e - rhs.e;
	return result;
}
Approach1::Equation operator *(Approach1::Equation lhs, const int* rhs) {
	lhs.a *= rhs[0];
	lhs.b *= rhs[1];
	lhs.c *= rhs[2];
	lhs.d *= rhs[3];
	lhs.e *= rhs[4];
	return lhs;
}
int Approach1::determine_order(std::vector<int>* input, int* constantDifference) {
	int first[5]{};
	int second[4]{};
	int third[3]{};
	//int fourth[2]{};
	if (input->at(1) - input->at(0) == input->at(2) - input->at(1)) { *constantDifference = input->at(1) - input->at(0); return 1; }
	for (int a = 0; a < 5; a++)
	{
		first[a] = input->at(a + 1) - input->at(a);
	}
	if (first[1] - first[0] == first[2] - first[1]) { *constantDifference = first[1] - first[0]; return 2; }
	for (int b = 0; b < 4; b++)
	{
		second[b] = first[b + 1] - first[b];
	}
	if (second[1] - second[0] == second[2] - second[1]) { *constantDifference = second[1] - second[0]; return 3; }
	for (int c = 0; c < 3; c++)
	{
		third[c] = second[c + 1] - second[c];
	}
	if (third[1] - third[0] == third[2] - third[1]) { *constantDifference = third[1] - third[0]; return 4; }
	return -1;
}

Approach::result Approach1::derive_function(const int* order, std::vector<int>* input, const int* constantDifference, const std::string* setName) {
	Equation formula{};
	std::array<std::array<Equation, 5>, 5> equations = std::array<std::array<Equation, 5>, 5>();
	setup_equations(&equations, order,input);
	for (int x = 1; x < (*order) + 1; x++)
	{
		for (int y = 0; y < (*order) + 1 - x; y++)
		{
			equations[x][y] = equations[x - 1][y + 1] - equations[x - 1][y];
		}
	}
	int firstCoeff = (*constantDifference) / factorial(*order);
	int terms[5]{};
	setup_coeffs(order, &firstCoeff, terms);
	
	for (int x = (*order); x > 0; x--)
	{
		Equation equation = equations[x - 1][0];
		equation = equation * terms;
		switch (x - 1) {
		case(0):
			terms[4] = (equation.y - equation.a - equation.b - equation.c - equation.d) / equation.e;
			break;
		case(1):
			terms[3] = (equation.y - equation.a - equation.b - equation.c - equation.e) / equation.d;
			break;
		case(2):
			terms[2] = (equation.y - equation.a - equation.b - equation.d - equation.e) / equation.c;
			break;
		case(3):
			terms[1] = (equation.y - equation.a - equation.c - equation.d - equation.e) / equation.b;
			break;
		}
	}
	//display_result(setName, terms);
	result r{ terms[0],terms[1],terms[2],terms[3],terms[4] };
	return r;
}

Approach::result Approach1::run(std::vector<int>* input, const std::string* setName) {
	for (int x = 0; x < 21; x++)
	{
		int constantDifference = -1;
		int order = determine_order(input, &constantDifference);
		result r = derive_function(&order, input, &constantDifference, setName);
		if (order == -1) std::cout << "order not detected";
		return r;
	}
}

void Approach1::setup_equations(std::array<std::array<Equation, 5>, 5>* equations, const int* order, const std::vector<int>* input) {
	for (int x = 0; x < (*order) + 1; x++)
	{
		equations->at(0).at(x).y = input->at(x);
		equations->at(0).at(x).a = *order >= 4 ? pow(x, 4) : 0;
		equations->at(0).at(x).b = *order >= 3 ? pow(x, 3) : 0;
		equations->at(0).at(x).c = *order >= 2 ? pow(x, 2) : 0;
		equations->at(0).at(x).d = *order >= 1 ? x : 0;
		equations->at(0).at(x).e = 1;
	}
}

void Approach1::setup_coeffs(const int* order, const int* firstCoeff, int* terms) {
	terms[0] = *order >= 4 ? (*order == 4 ? *firstCoeff : 1) : 0;
	terms[1] = *order >= 3 ? (*order == 3 ? *firstCoeff : 1) : 0;
	terms[2] = *order >= 2 ? (*order == 2 ? *firstCoeff : 1) : 0;
	terms[3] = *order >= 1 ? (*order == 1 ? *firstCoeff : 1) : 0;
	terms[4] = 1;
}