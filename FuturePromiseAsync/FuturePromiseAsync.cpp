// FuturePromiseAsync.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include<iostream>
#include<fstream>
#include <thread>
#include<future>
#include<string>
#include<mutex>

using namespace std;

int factorial(int N)
{
	int res = 1;
	for (int i = N; i > 1; i--)
		res *= i;

	cout << "Child Result is: " << res << endl;
	return res;
}

int future_factorial(std::future<int>& f)
{
	int res = 1;
	int N = f.get(); // exception: std::future_errc::broken_promise, no promised value given

	for (int i = N; i > 1; i--)
		res *= i;

	cout << "Child Result(future) is: " << res << endl;
	return res;
}

int main()
{
	int x;
	//std::thread t1(factorial, 4, std::ref(x));

	// Using async to not initiate another thread, wait until future (fu) is called, same thread
	//std::future<int> fu = std::async(std::launch::deferred, factorial, 4);
	
	// Force async to initiate another thread
	//std::future<int> fu = std::async(std::launch::async, factorial, 4);
	
	// Let implementaiton determine if async initiates another thread (Default)
	//std::future<int> fu = std::async(std::launch::async | std::launch::deferred, factorial, 4);

	std::future<int> fu1 = std::async(std::launch::async, factorial, 4);
	//waits until child thread is finished and can only be called once
	x = fu1.get(); 
	cout << "Returned value: " << x << endl;


	int y;

	std::promise<int> p;
	std::future<int> f = p.get_future();

	std::future<int> fu2 = std::async(std::launch::async, future_factorial, std::ref(f));
	

	// do something else
	std::this_thread::sleep_for(chrono::milliseconds(20));

	//p.set_exception(std::make_exception_ptr(std::runtime_error("To err is human")));
	p.set_value(5);

	y = fu2.get();
	cout << "Returned(future) value: " << y << endl;

	//t1.join();
	getchar();
    return 0;
}

