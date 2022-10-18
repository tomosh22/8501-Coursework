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
//class Thread {
//public:
//    Thread() {};
//    virtual ~Thread() { CloseHandle(thread_handle); }
//    virtual void start();
//    virtual void join();
//    virtual DWORD get_id() const { return tid; }
//protected:
//    virtual void run() = 0;
//    friend DWORD thread_ftn(LPVOID T);
//    HANDLE thread_handle;
//    DWORD tid;
//private:
//    Thread(const Thread& src);
//    Thread& operator=(const Thread& rhs);
//};
//DWORD thread_ftn(LPVOID T) {
//    Thread* t = static_cast<Thread*>(T);
//    t->run();
//    return NULL;
//}
//void Thread::start() {
//    thread_handle = CreateThread(
//        NULL,
//        0,
//        (LPTHREAD_START_ROUTINE)&thread_ftn,
//        (LPVOID)this,
//        0,
//        &tid
//    );
//}
//void Thread::join() {
//    WaitForSingleObject(thread_handle, INFINITE);
//}







void create_set() {
	std::cout << "ax^4 + bx^3 + cx^2 + dx + e\n";
	int terms[5];
	std::map<int, char> charMap;
	charMap[0] = 'a';
	charMap[1] = 'b';
	charMap[2] = 'c';
	charMap[3] = 'd';
	charMap[4] = 'e';
	for (int x = 0; x < 5; x++)
	{
		do {
			std::cout << "input value from 0-9 for " << charMap[x] << '\n';
			std::cin >> terms[x];
		} while (terms[x] > 9);
	}
	int lower = 0;
	int upper = 0;
	int values[21];
	do {
		std::cout << "range of input set must be 21 or less\n";
		std::cout << "input value for lower bound of input set\n";
		std::cin >> lower;
		std::cout << "input value for upper bound of input set\n";
		std::cin >> upper;
	} while (upper - lower > 20);
	
	for (int x = lower; x <= upper; x++)
	{
		int value = terms[0] * (int)pow(x, 4)
			+ terms[1] * (int)pow(x, 3)
			+ terms[2] * (int)pow(x, 2)
			+ terms[3] * x
			+ terms[4];
		values[x - lower] = value;
		std::cout << value << ' ';
	}
	std::cout << '\n';
	std::cout << "output to file? Y : N\n";
	char choice;
	std::cin >> choice;
	char name[10]{};
	if (choice == 'Y' || choice == 'y') {
		
		std::cout << "input set name (max 10 chars)\n";
		std::cin >> name;
		std::cout << name << '\n';
	}
	try {
		std::ofstream file("sets.csv", std::ios::app);
		file << name;
		for (int x = lower; x <= upper; x++)
		{
			file << ',' << values[x - lower];
		}
		file << '\n';
		file.close();
	}
	catch (std::ofstream::failure e) {
		std::cout << e.what();
	}
	
	return;
}

void read_sets(std::map<std::string, std::array<int,21>>* setsMap) {
	std::ifstream file("sets.csv", std::ios::in);
	std::map<std::string, int*> readSets;
	std::string line;
	char chr;
	char value[10]{};//can only read integers up to 9999999999
	int valueIndex = 0;
	int setIndex = 0;
	bool nameFound = false;
	std::string setName;
	try {
		if (!file.is_open()) { throw std::ifstream::failure("Error reading file"); }
		while (file.get(chr)) {
				if (chr == '\n') {
					valueIndex = 0; (*setsMap)[setName][setIndex++] = std::stoi(value);
					for (int x = 0; x < 10; x++)
					{
						value[x] = '\0';
					}
					nameFound = false; setName = ""; setIndex = 0; continue; }
				if (!nameFound) {
					if (chr == ',') {
						nameFound = true;
						continue;
					}
					setName.push_back(chr);
				}
				else {
					if (chr == ',') {
				
						valueIndex = 0; (*setsMap)[setName][setIndex++] = std::stoi(value);
						for (int x = 0; x < 10; x++)
						{
							value[x] = '\0';
						}
						continue; }
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


void cli(std::map<std::string, std::array<int, 21>>* setsMap) {
	char choice;
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
			read_sets(setsMap);
			break;
		case '3':
			system("CLS");
			for (std::pair<std::string, std::array<int, 21>> pair : *setsMap) {
				Approach2Namespace::run(&pair.second, &pair.first);
			}
			//std::string setName;
			//std::cin >> setName;
			//Approach2Namespace::run(&setsMap->at(setName));
			break;
		case '4':
			return;
		}

	}
}
	

int main()
{
	std::map<std::string, std::array<int, 21>> setsMap;
	//cli(&setsMap);
	read_sets(&setsMap);
	std::map<int, std::string> charMap;
	charMap[0] = "a";
	charMap[1] = "b";
	charMap[2] = "c";
	charMap[3] = "d";
	charMap[4] = "e";
	charMap[5] = "f";
	std::thread threads[6]{};

	/*Approach2 solver = Approach2();
	std::string name = "a";
	solver.run(&(setsMap.at(charMap.at(0))),&name);*/

	//return 0;
	for (int x = 0; x < 6; x++)
	{
		Approach2 solver = Approach2();
		std::array<int, 21 >* input = &(setsMap.at(charMap.at(x)));
		std::string* setName = &charMap.at(x);
		auto func = [](std::array<int, 21 >* input, std::string* setName, Approach2 solver) {
			solver.run(input,setName);
		};
		std::cout << "starting thread " << x << '\n';
		threads[x] = std::thread(func,input,setName,solver);
	}
	for (int x = 0; x < 6; x++) {
		
		threads[x].join();
	}
	
	return 0;
}

