// DataRaceAndMutex.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include<iostream>
#include<fstream>
#include <thread>
#include<string>
#include<mutex>

using namespace std;

std::mutex mu;

/*
 * The mutex class is a synchronization primitive that can 
  * be used to protect shared data from being simultaneously 
  * accessed by multiple threads.
  */

/*
 * RAII- Resource Acquisition Is Initialization, 
 *  is a C++ programming technique which binds the life cycle
 *	of a resource that must be acquired before use 
 *	(allocated heap memory, thread of execution, open socket, 
 *	open file, locked mutex, disk space, 
 * 	database connection—anything that exists in limited supply)
 *	to the lifetime of an object. 
 */

class LogFile {
	std::mutex _mu;
	ofstream _f;
public:
	LogFile()
	{
		_f.open("log.txt");
	} // need destructor to close file

	void shared_print(string id, int value)
	{
		std::lock_guard<mutex> locker(_mu);
		_f << "From " << id << ": " << value << endl;
	}

	// Never return f to the outside world
	// e.g. ofstream& getStream() { return f;}
	//Never pass f as an argument to user provided function
	// void processf(void fun(ofstream&)) {
	//		fun(f);
	// }
};

void function_1(LogFile& log)
{
	for (int i = 0; i > -100; i--)
	{
		//cout << "From t1: " << i << endl;
		log.shared_print(string("t1: "), i);
	}
}

int main()
{
	LogFile log;
	std::thread t1(function_1, std::ref(log));

	for (int i = 0; i < 100; i++)
	{
		//cout << "From main: " << i << endl;
		//shared_print(string("From main: "), i);
		log.shared_print(string("From main: "), i);
	}

	t1.join();

    return 0;
}

