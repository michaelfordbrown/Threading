// Deadlock.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include<iostream>
#include<fstream>
#include <thread>
#include<string>
#include<mutex>

using namespace std;

class LogFile {
	std::mutex _mu1;
	std::mutex _mu2;
	ofstream _f;
public:
	LogFile()
	{
		_f.open("log.txt");
	} // need destructor to close file

	void shared_print1(string id, int value)
	{
		/*
		 * std::lock_guard<mutex> locker1(_mu1);
		 * std::lock_guard<mutex> locker2(_mu2);
		 */

		/*
		* std::lock function allows multiple mutex to be locked
		* and includes deadlock algorithms.
		*/

		/*
		 * std::adopt_lock tells locker that mutex already locked 
		 * and needs to adopt the ownership of mutex to close 
		 * when out of scope
		 */
		std::lock(_mu1, _mu2);
		std::lock_guard<mutex> locker1(_mu1, std::adopt_lock);
		std::lock_guard<mutex> locker2(_mu2, std::adopt_lock);


		cout << "From " << id << ": " << value << endl;
	}

	void shared_print2(string id, int value)
	{
		/*
		 * Multiple mutex locked in the same order as shared_print1
		 * This helps avoid deadlocks.

			std::lock_guard<mutex> locker1(_mu1);
			std::lock_guard<mutex> locker2(_mu2);
		*/

		/*
		 * std::lock(_mu1, _mu2);
		 * std::lock_guard<mutex> locker2(_mu2, std::adopt_lock);
		 * std::lock_guard<mutex> locker1(_mu1, std::adopt_lock);
		 */
		/*
		 * To avoid deadlock best to keep mutex locked down to minimum
		 * When multiple mutex needed best target within code.
		 */
		{
			std::lock_guard<mutex> locker1(_mu1);
			// Do things here
		}
		{
			std::lock_guard<mutex> locker2(_mu2);
			cout << "From " << id << ": " << value << endl;
		}


		cout << "From " << id << ": " << value << endl;
	}

	/* 
	 * Avoiding Deadlock
	 * 1. Prefer locking single mutex.
	 * 2. Avoid locking a mutex and then calling a user provided function
	 * 3. Use std::lock() to lock more than one mutex
	 * 4. Lock the mutex in same order (e.g. use hierarchy)
	 */
};

void function_1(LogFile& log)
{
	for (int i = 0; i > -100; i--)
	{
		log.shared_print2(string("t1: "), i);
	}
}

int main()
{
	LogFile log;
	std::thread t1(function_1, std::ref(log));

	for (int i = 0; i < 100; i++)
	{
		log.shared_print1(string("From main: "), i);
	}

	t1.join();

	getchar();

	return 0;
}


