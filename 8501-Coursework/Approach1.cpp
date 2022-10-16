#include "Approach1.h"
#include <iostream>
#include <array>
namespace Approach1 {
	struct Equation {
		int y; //from input
		int a; //x^4
		int b; //x^3
		int c; //x^2
		int d; //x
		int e; //constant
	};
	Equation operator-(const Equation lhs, const Equation rhs) {
		Equation result;
		result.y = lhs.y - rhs.y;
		result.a = lhs.a - rhs.a;
		result.b = lhs.b - rhs.b;
		result.c = lhs.c - rhs.c;
		result.d = lhs.d - rhs.d;
		result.e = lhs.e - rhs.e;
		return result;
	}
	
	int factorial(int num) {
		if (num == 1) { return 1; }
		return num * factorial(num - 1);
	}
	result derive_function(const int* order, std::array<int, 21 >* input, const int* constantDifference) {
		Equation formula{};
		Equation equations[5][5] = {};
		//todo change this to start at index 0 to reduce required number of inputs

		for (int x = 0; x < (*order) + 1; x++)
		{
			equations[0][x].y = input->at(x+1);
			equations[0][x].a = *order >= 4 ? pow(x + 1, 4) : 0;
			equations[0][x].b = *order >= 3 ? pow(x + 1, 3) : 0;
			equations[0][x].c = *order >= 2 ? pow(x + 1, 2) : 0;
			equations[0][x].d = *order >= 1 ? x + 1 : 0;
			equations[0][x].e = 1;
		}
		for (int x = 1; x < (*order) + 1; x++)
		{
			for (int y = 0; y < (*order) + 1 - x; y++)
			{
				equations[x][y] = equations[x - 1][y + 1] - equations[x - 1][y];
			}
		}
		int firstCoeff = (*constantDifference) / factorial(*order);
		int a = *order >= 4 ? (*order == 4 ? firstCoeff : 1) : 0;
		int b = *order >= 3 ? (*order == 3 ? firstCoeff : 1) : 0;
		int c = *order >= 2 ? (*order == 2 ? firstCoeff : 1) : 0;
		int d = *order >= 1 ? (*order == 1 ? firstCoeff : 1) : 0;
		int e = 1;
		for (int x = (*order); x > 0; x--)
		{
			Equation equation = equations[x - 1][0];
			equation.a *= a;
			equation.b *= b;
			equation.c *= c;
			equation.d *= d;
			equation.e *= e;
			switch (x - 1) {
			case(0):
				e = (equation.y - equation.a - equation.b - equation.c - equation.d) / equation.e;
				break;
			case(1):
				d = (equation.y - equation.a - equation.b - equation.c - equation.e) / equation.d;
				break;
			case(2):
				c = (equation.y - equation.a - equation.b - equation.d - equation.e) / equation.c;
				break;
			case(3):
				b = (equation.y - equation.a - equation.c - equation.d - equation.e) / equation.b;
				break;
			}
		}
		std::cout << a << "x^4 + " << b << "x^3 + " << c << "x^2 + " << d << "x + " << e << '\n';
		result r{ a,b,c,d,e };
		return r;
	}
	int determine_order(std::array<int, 21 > *input, int* constantDifference) {
		int first[5]{};
		int second[4]{};
		int third[3]{};
		//int fourth[2]{};
		if (input->at(1) - input->at(0) == input->at(2) - input->at(1) ){ *constantDifference = input->at(1) - input->at(0); return 1; }
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
	result run(std::array<int, 21 > *input) {
		//while true(){}
		for (int x = 0; x < 21; x++)
		{
			int constantDifference = -1;
			int order = determine_order(input, &constantDifference);
			result r = derive_function(&order, input, &constantDifference);
			if (order == -1) { std::cout << "order not detected"; }
			return r;
		}
	}
}