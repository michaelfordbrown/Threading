// Introdcution.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <thread>
using namespace std;

void function_1() {
	std::cout << "Beauty is only skin-deep" << std::endl;
}

int main()
{
	std::thread t1(function_1); // t1 starts running

	//t1.join();	// main thread waits for t1 to finish
	//t1.detach(); // t1 will freely run on its own -- daemon process

	if (t1.joinable())
		t1.join();  // After detach will cause a crash

    return 0;
}

