// FutureExcecptionHanndling.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <thread>
#include <future>
#include <iostream>

#define OUTOFRANGE 2
#define FACMAX 12

int single_thread_factorial(int N)
{
	long res = 1;

	if (N > 12)
	{
		std::cout << "Factorial Out of INT Range of : " << INT_MAX << std::endl;
		throw OUTOFRANGE;
	}
	else
	{
		for (long i = N; i > 1; i--)
			res *= i;

		std::cout << "Factorial of " << N << " is\t" << res << std::endl;
		}
	return (int)res;
}

int multi_thread_factorial(int N)
{
	long res = 1;

	if (N > 10)
	{
		throw std::runtime_error("ERROR: Factorial Out of INT Range");
	}
	else
	{
		for (long i = N; i > 1; i--)
			res *= i;

		std::cout << "Factorial of " << N << " is\t" << res << "\t\tOn Thread:\t" << std::this_thread::get_id() << std::endl;
	}

	return (int)res;
}


void single_thread_test()
{
	std::cout << "\nSingle Thread Test\n";

	try
	{
		std::cout << "INT MAX on this machine is :" << INT_MAX << std::endl;
		for (int x = 0; x < FACMAX; x++)
		{
			single_thread_factorial(x);
		}
	}
	catch (int e)
	{
		switch (e)
		{
			case OUTOFRANGE:
			{
				std::cout << "\nERROR: Out Of Range!\n";
				break;
			}
			default:
			{
				std::cout << "\nERROR: Unknown Error Event!\n";
			}
		}
	}

}

void multi_thread_test()
{
	std::cout << "\nMulti Thread Test\n";

	std::promise<int> p;
	std::future<int> f = p.get_future();

	try
	{
		std::cout << "INT MAX on this machine is :" << INT_MAX << std::endl;

		for (int x = 0; x < FACMAX; x++)
		{
			std::future<int> fu1 = std::async(std::launch::async, multi_thread_factorial, x);
		}
	}
	catch (const std::exception& e)
	{
		std::cout << "exception caught: " << e.what() << std::endl;
	}

}
int main()
{
	std::cout << "Future Event Handling\n";

	single_thread_test();

	std::cout << std::endl;

	multi_thread_test();

	getchar();
    return 0;
}

