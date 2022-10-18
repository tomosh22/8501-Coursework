#pragma once
#include <array>
#include <string>
#include <iostream>
class Approach {
public:
	Approach() {};
	~Approach() {};
	
	struct result {
		int a; //x^4
		int b; //x^3
		int c; //x^2
		int d; //x
		int e; //constant
	};
	virtual result run(std::array<int, 21 >* input, const std::string* setName) = 0;
	static void display_result(const std::string* setName, const result* result);
protected:
	
	int  factorial(int num);
	
};