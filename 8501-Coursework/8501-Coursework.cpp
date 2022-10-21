#include <iostream>
#include "Sets.h"
#include <thread>
#include <map>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <array>
#include <functional>
#include "Approach.h"
#include "Approach1.h"
#include "Approach2.h"
#include <vector>
#include <math.h>
#include <limits>

std::map<int, char> create_char_map() {
	std::map<int, char> charMap;
	charMap[0] = 'a';
	charMap[1] = 'b';
	charMap[2] = 'c';
	charMap[3] = 'd';
	charMap[4] = 'e';
	return charMap;
}

bool string_is_number(std::string* input) {
	for (char const& c : *input) {
		if (!std::isdigit(c)) {
			return false;
		}
	}
	return true;
}

void get_terms_from_user(int* terms, const std::map<int, char>* charMap) {
	std::string input;
	for (int x = 0; x < 5; x++){
		while(true) {
			std::cout << "input value for " << charMap->at(x) << '\n';
			std::cin >> input;
			if (!string_is_number(&input))continue;
			break;
		}
		terms[x] = std::stoi(input);
	}
}



void get_lower_bound_from_user(int* lower, std::string* input) {
	bool isNumber;
	while(true) {
		std::cout << "input value for lower bound of input set\n";
		std::cin >> *input;
		if (!string_is_number(input))continue;
		break;
	}
	*lower = std::stoi(*input);
}

void get_upper_bound_from_user(int* upper, int* lower, std::string* input) {
	while(true){
		std::cout << "input value for upper bound of input set (must be greater than " << *lower << ")\n";
		std::cin >> *input;
		if (!string_is_number(input))continue;
		if (std::stoi(*input) > *lower)break;
	}
	*upper = std::stoi(*input);
}

void get_input_set_from_user(int* lower, int* upper) {
	std::string input;
	get_lower_bound_from_user(lower, &input);
	get_upper_bound_from_user(upper, lower, &input);
}

void generate_set_from_input_set(std::vector<int>* values, const int* terms, const int* lower, const int* upper) {
	for (int x = *lower; x <= *upper; x++){
		int value = terms[0] * (int)pow(x, 4)
			+ terms[1] * (int)pow(x, 3)
			+ terms[2] * (int)pow(x, 2)
			+ terms[3] * x
			+ terms[4];
		values->push_back(value);
		std::cout << value << ' ';
	}
}

void write_set_to_file(const std::vector<int>* values) {
	try {
		std::ofstream file("sets.csv", std::ios::app);
		file << values->at(0);
		for (int x = 1; x < values->size(); x++){
			file << ',' << values->at(x);
		}
		file << '\n';
		file.close();
	}
	catch (std::ofstream::failure e) {
		std::cout << e.what();
	}
}

void create_set() {
	std::cout << "ax^4 + bx^3 + cx^2 + dx + e\n";
	int terms[5],lower,upper;
	std::map<int, char> charMap = create_char_map();
	get_terms_from_user(terms, &charMap);
	std::vector<int> values;
	get_input_set_from_user(&lower,&upper);
	generate_set_from_input_set(&values, terms, &lower, &upper);
	std::cout << "\noutput to file? Y : N\n";
	char choice;
	std::cin >> choice;
	if (choice == 'Y' || choice == 'y') write_set_to_file(&values);
	return;
}

void handle_new_line(int* valueIndex, int* setIndex, char* value, std::vector<std::vector<int>>* sets, int* mapIndex) {
	*valueIndex = 0;
	sets->at(*(mapIndex)).push_back(std::stoi(value));
	for (int x = 0; x < 9; x++) {
		value[x] = '\0';
	}
	*setIndex = 0;
	*mapIndex = *mapIndex + 1;
	return;
}

void handle_new_value(int* valueIndex, int* setIndex,  char* value, std::vector<std::vector<int>>* sets, int* mapIndex) {
	*valueIndex = 0;
	if (sets->size() < (*mapIndex)+1) sets->push_back(std::vector<int>());
	sets->at(*(mapIndex)).push_back(std::stoi(value));
	for (int x = 0; x < 9; x++) {
		value[x] = '\0';
	}
}

void read_sets(std::vector<std::vector<int>>* sets) {
	std::ifstream file("sets.csv", std::ios::in);
	std::map<std::string, int*> readSets;
	std::string line;
	char chr, value[9]{};//can only read integers up to 999999999
	int valueIndex = 0, setIndex = 0, mapIndex = 0;
	try {
		if (!file.is_open()) throw std::ifstream::failure("Error reading file");
		while (file.get(chr)) {
			if (valueIndex >= 9) {
				std::cout << "error: value greater than 999999999\n";
				return;
			}
			if (chr == '\n') {
				handle_new_line(&valueIndex, &setIndex, value, sets, &mapIndex);
				continue;
			}
			else {
				if (chr == ',') {
					handle_new_value(&valueIndex, &setIndex, value, sets, &mapIndex);
					continue;
				}
				else { value[valueIndex++] = chr; }
			}
		}
	}
	catch (const std::ios_base::failure& e) {
		std::cout << e.what() << "\nSpace - Enter to continue";
		while (true) { if (std::cin.get() == ' ') { break; } }
		system("CLS");
	}
	return;
}

template <typename T>
void create_threads(std::vector<std::vector<int>>* sets, std::vector<std::thread>* threads, std::vector<Approach::result>* results, T* solver) {
	for (int x = 0; x < sets->size(); x++) {
		results->push_back({});
	}
	for (int x = 0; x < sets->size(); x++) {
		auto func = [](std::vector<int>* set, std::vector<Approach::result>* results, T* solver, int x) {
			Approach::result r = solver->run(set);
			results->at(x) = r;
		};
		threads->push_back(std::thread(func, &sets->at(x), results, solver,x));
	}
	for (std::thread& thread : *threads){
		thread.join();
	}
	threads->clear();
}

void write_expressions_to_file(const std::vector<Approach::result>* results) {
	try {
		std::ofstream file("expressions.csv", std::ios::out);
		for (int x = 0; x < results->size();x++) {
			Approach::display_result(&results->at(x));
			file << ' ' << Approach::result_string(&results->at(x));
			file << '\n';
		}
		file.close();
	}
	catch (std::ofstream::failure e) {
		std::cout << e.what();
	}
}

Approach* get_approach_from_user() {
	char input;
	do {
		std::cout << "1 for Approach1\n2 for Approach2\n";
		std::cin >> input;
	} while (input != '1' && input != '2');
	return (input == '1') ? (Approach*)(new Approach1()) : (Approach*)(new Approach2());
}

void experimental(std::vector<std::vector<int>>* sets) {
	Approach2 solver = Approach2();
	std::string f = "5";
	float x = 6;
	//std::cout << x << std::endl;
	while (x < 8) {
		Approach::result r = solver.run_experimental(&sets->at(5), &x);
		//std::cout << x << '\n';
		if (std::abs(r.d) < 9 && std::abs(r.e) < 1000) {
			std::cout << x << '\n';
			Approach::display_result(&r);
			std::cout << '\n';
		}
		//x = std::nextafterf(x, FLT_MAX);

		x += (float)1 / 4096;
	}
	/*for (float x = 6; x < 8; x+= std::numeric_limits<float>::min()) {
		Approach::result r = solver.run_experimental(&sets->at(5), &x);
		
		if( std::abs(r.d) < 9 && std::abs(r.e) < 1000){
			std::cout << x << '\n';
			Approach::display_result(&r);
			std::cout << '\n';
		}
		
		
	}*/
}

void cli(std::vector<std::vector<int>>* sets) {
	char choice;
	std::vector<std::thread> threads;
	std::vector<Approach::result> results;
	Approach* solver = get_approach_from_user();
	while (true) {
		std::cout << "1. create set\n2. read sets\n3. derive formula from set\n4. Set F\n";
		std::cin >> choice;
		switch (choice){
		case '1':
			system("CLS");
			create_set();
			break;
		case '2':
			system("CLS");
			read_sets(sets);
			break;
		case '3':
			if (sets->size() == 0) {
				system("CLS");
				std::cout << "no sets read\nSpace - Enter to continue";
				while (true) { if (std::cin.get() == ' ') { break; } }
				system("CLS");
				break;
			}
			system("CLS");
			create_threads(sets, &threads, &results, solver);
			write_expressions_to_file(&results);
			break;
		case '4':
			if (sets->size() == 0) {
				system("CLS");
				std::cout << "no sets read\nSpace - Enter to continue";
				while (true) { if (std::cin.get() == ' ') { break; } }
				system("CLS");
				break;
			}
			experimental(sets);
			return;
		default:

			system("CLS");
			break;
		}
	}
}
	

int main()
{
	std::vector<std::vector<int>> sets;
	cli(&sets);
	return 0;
}

