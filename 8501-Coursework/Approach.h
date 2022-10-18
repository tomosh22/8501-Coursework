#pragma once
#include <array>
#include <string>
#include <iostream>
class Approach {
public:
	Approach() {};
	~Approach() {};
	virtual void run(std::array<int, 21 >* input, const std::string* setName) {};
protected:
	void display_result(const std::string* setName, const int* terms);
	int factorial(int num);
	struct result {
		int a; //x^4
		int b; //x^3
		int c; //x^2
		int d; //x
		int e; //constant
	};
};