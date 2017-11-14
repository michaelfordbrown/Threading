// ThreadManagement.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include<iostream>
#include<thread>
#include<string>

using namespace std;

void function_1() {
	std::cout << "from thread " << std::this_thread::get_id() << " says: Beauty is only skin-deep" << std::endl;
}

/*
 * Function Operator
 */
class Fctor {
public:
	void operator()() {
		for (int i = 0; i > -20; i--) {
			cout << "from thread " << std::this_thread::get_id() <<  " " << i << endl;
		}
	}
}; 

class FctorWithP{
public:
	void operator()(std::string& msg) {
		cout << "from thread " << std::this_thread::get_id() <<" says: " << msg << endl;
		msg = "Trust is the mother of deceit.";
	}
};

int main()
{
	string s = "Where there is no trust there is no love.";

	cout << "C++ Thread Management" << endl << endl;

	/*
	 * static unsigned int hardware_concurrency() noexcept; (since C++11)
     * Returns the number of concurrent threads supported by the implementation. 
	 * The value should be considered only a hint. 
	 */
	unsigned int ConcurrentThreadsSupported = std::thread::hardware_concurrency();
	if (ConcurrentThreadsSupported > 0)
		cout << "Number of concurrent threads supported: " << ConcurrentThreadsSupported << endl;
	else
		cout << "Number of concurrent threads supported not defined." << endl << endl;

	
	Fctor fct;
	
	std::thread t1(function_1); // t1 starts running
	std::thread t2((Fctor())); // t2 starts running. note extra () around Fctor
	std::thread t3((FctorWithP()), std::ref(s)); // t3. Extra () around Fctor also use ref for reference (sharing memory) otherwise copy only
	std::thread t4((FctorWithP()), std::move(s)); // t4. Use move to relocate variable 's' from main thread to child thread (not a copy)

	std::thread t5 = std::move(t4);

	/*
	 * try .. catch block used to capture exceptions 
	  * and ensure that main thread waits for the minor threads to complete.
	  *
	  * Alternative approach is RAII (Resource Acquisition Is Initialization)
	  * by creating a wrapper class around the thread . . w(t1) where destructor calls join.
	   * When the wrapper goes out of scope it will join the threat
	 */
	try {

		for (int i = 0; i < 20; i++)
			cout << "from main thread (" << std::this_thread::get_id() << "): " << i << endl;
	}
	catch (...) 
	{
		t1.join();
		t2.join();
		t3.join();
		// t4.join();
		t5.join();
		throw;
	}

	/*
	 * Force main to wait until threads are completed
	 */
	t1.join(); 
	t2.join();
	t3.join();
	// t4.join();
	t5.join();

	cout << "from main thread (" << std::this_thread::get_id() << "): " << s << endl;

    return 0;
}

