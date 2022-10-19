#include <iostream>
#include "Approach1Namespace.h"
#include "Approach2Namespace.h"
#include "Sets.h"
//#include <windows.h>
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

std::map<int, char> create_char_map() {
	std::map<int, char> charMap;
	charMap[0] = 'a';
	charMap[1] = 'b';
	charMap[2] = 'c';
	charMap[3] = 'd';
	charMap[4] = 'e';
	return charMap;
}

void get_terms_from_user(int* terms, const std::map<int, char>* charMap) {
	for (int x = 0; x < 5; x++)
	{
		do {
			std::cout << "input value from 0-9 for " << charMap->at(x) << '\n';
			std::cin >> terms[x];
			//} while (terms[x] > 9);
		} while (false);
	}
}

void get_input_set_from_user(int* lower, int* upper) {
	do {
		//std::cout << "range of input set must be 21 or less\n";
		std::cout << "input value for lower bound of input set\n";
		std::cin >> *lower;
		std::cout << "input value for upper bound of input set\n";
		std::cin >> *upper;
		//} while (*upper - *lower > 20);
	} while (false);
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
		for (int x = 0; x <= values->size(); x++)
		{
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
	int terms[5];
	std::map<int, char> charMap = create_char_map();
	get_terms_from_user(terms, &charMap);
	int lower = 0;
	int upper = 0;
	std::vector<int> values;
	get_input_set_from_user(&lower,&upper);
	generate_set_from_input_set(&values, terms, &lower, &upper);
	
	std::cout << '\n';
	std::cout << "output to file? Y : N\n";
	char choice;
	std::cin >> choice;
	
	if (choice == 'Y' || choice == 'y') {
		write_set_to_file(&values);
	}
	
	
	return;
}

void handle_new_line(int* valueIndex, int* setIndex, char* value, std::vector<std::vector<int>>* sets, int* mapIndex) {
	*valueIndex = 0;
	sets->at(*(mapIndex)).push_back(std::stoi(value));
	for (int x = 0; x < 10; x++) {
		value[x] = '\0';
	}
	*setIndex = 0;
	*mapIndex = *mapIndex + 1;
	return;
}

void handle_new_value(int* valueIndex, int* setIndex,  char* value, std::vector<std::vector<int>>* sets, int* mapIndex) {
	*valueIndex = 0;
	if (sets->size() < (*mapIndex)+1)sets->push_back(std::vector<int>());
	sets->at(*(mapIndex)).push_back(std::stoi(value));
	for (int x = 0; x < 10; x++) {
		value[x] = '\0';
	}
}

void read_sets(std::vector<std::vector<int>>* sets) {
	std::ifstream file("sets.csv", std::ios::in);
	std::map<std::string, int*> readSets;
	std::string line;
	char chr;
	char value[10]{};//can only read integers up to 9999999999
	int valueIndex = 0;
	int setIndex = 0;
	int mapIndex = 0;
	try {
		if (!file.is_open()) throw std::ifstream::failure("Error reading file");
		while (file.get(chr)) {
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
void create_threads(std::vector<std::vector<int>>* sets, std::vector<std::thread>* threads, std::map<int, Approach::result>* results, T* solver) {
	for (int x = 0; x < sets->size(); x++) {
		auto func = [](std::vector<int>* set, std::map<int, Approach::result>* results, T* solver, int x) {
			Approach::result r = solver->run(set);
			results->insert({ x,r });
		};
		threads->push_back(std::thread(func, &sets->at(x), results, solver,x));
	}
	for (std::thread& thread : *threads)
	{
		thread.join();
	}
}

void cli(std::vector<std::vector<int>>* sets) {
	char choice;
	std::vector<std::thread> threads;
	std::map<int, Approach::result> results;
	Approach1 solver = Approach1();
	while (true) {
		std::cout << "1. create set\n2. read sets\n3. derive formula from set\n";
		std::cin >> choice;
		switch (choice)
		{
		case '1':
			system("CLS");
			create_set();
			break;
		case '2':
			system("CLS");
			read_sets(sets);
			break;
		case '3':
			system("CLS");
			create_threads(sets, &threads, &results, &solver);
			threads.clear();
			try {
				std::ofstream file("expressions.csv", std::ios::out);
				for (std::pair<int, Approach::result> pair : results) {
					Approach::display_result(&pair.second);
					file << ' ' << Approach::result_string(&pair.second);
					file << '\n';
				}
				file.close();
			}
			catch (std::ofstream::failure e) {
				std::cout << e.what();
			}
			
			break;
		case '4':
			Approach2 solver = Approach2();
			std::string f = "5";
			for (int x = -50; x < 50; x++)
			{
				Approach::result r = solver.run_experimental(&sets->at(5), &x);
				Approach::display_result(&r);
				std::cout <<'\n' << x << '\n';
			}
			return;
		}
	}
}
	

int main()
{
	std::vector<std::vector<int>> sets;
	cli(&sets);
	
	return 0;
}

