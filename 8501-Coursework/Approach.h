#pragma once
#include <array>
#include <string>
#include <iostream>
#include <vector>
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
	virtual result run(std::vector<int>* input) = 0;
	static void display_result(const result* result);
	static std::string result_string(const result* result);
protected:
	
	int  factorial(int num);
	
};