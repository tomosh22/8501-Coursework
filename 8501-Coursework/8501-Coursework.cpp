#include <iostream>
#include "Approach1.h"
#include "Approach2.h"
#include "Sets.h"
//#include <windows.h>
#include <thread>
#include <map>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <array>
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
	std::ofstream file("sets.csv", std::ios::app);
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
	file << name;
	for (int x = lower; x <= upper; x++)
	{
		file << ',' << values[x - lower];
	}
	file << '\n';
	file.close();
	return;
}

void read_set(std::map<std::string, std::array<int,21>>* setsMap) {
	std::ifstream file("sets.csv", std::ios::in);
	std::map<std::string, int*> readSets;
	std::string line;
	char chr;
	char value[10]{};//can only read integers up to 9999999999
	int valueIndex = 0;
	int setIndex = 0;
	bool nameFound = false;
	std::string setName;
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
			if (chr == ',') { valueIndex = 0; (*setsMap)[setName][setIndex++] = std::stoi(value); continue; }
			else { value[valueIndex++] = chr; }
		}
	}
	return;
}


void cli(std::map<std::string, std::array<int, 21>>* setsMap) {
	char choice;
	while (true) {
		std::cout << "1. create set\n2. read set";
		std::cin >> choice;
		switch (choice)
		{
		case '1':
			system("CLS");
			create_set();
			break;
		case '2':
			system("CLS");
			read_set(setsMap);
			break;
		}
	}
}
	

int main()
{
	std::map<std::string, std::array<int, 21>> setsMap;
	cli(&setsMap);
	
	/*setsMap[0] = Sets::a;
	setsMap[1] = Sets::b;
	setsMap[2] = Sets::c;
	setsMap[3] = Sets::d;
	setsMap[4] = Sets::e;
	setsMap[5] = Sets::f;*/
	std::thread threads[6]{};
	Approach1::result results[6];
	for (int x = 0; x < 6; x++)
	{
		//threads[x] = std::thread(Approach1::run, setsMap[x]);
	}
	for (int x = 0; x < 6; x++) {
		threads[x].join();
	}
	
	return 0;
}

