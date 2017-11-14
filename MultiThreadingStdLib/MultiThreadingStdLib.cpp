// MultiThreadingStdLib.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include<thread>
#include<iostream>
#include<algorithm>
#include<vector>
#include<string>

using namespace std;

double sum1 = 0;
double sum2 = 0;

struct myclass {
	bool operator() (int i, int j) { return (i < j); }
}myobject;

vector<int> myvector;

void task1()
{
	cout << "task1 is starting..." << endl;
	double c = 0;
	while (c < 25000000)
	{
		c++;
		sum1 += c;
	}
	cout << "task 1 is completed..." << endl;
}

void task2()
{
	cout << "task2 is starting..." << endl;
	double c = 0;
	while (c < 2500000)
	{
		c++;
		sum2 += c;
	}
	cout << "task 2 is completed..." << endl;
}

void task3()
{
	cout << "task3 is starting..." << endl;
	myvector = { 12, 33, 22, 44, 15, 66, 46, 39, 72 };
	std::sort(myvector.begin(), myvector.end(), myobject);
	cout << "task 3 is completed..." << endl;
}



int main()
{

	thread t1(task1);
	thread t2(task2);
	thread t3(task3);
	
	thread::id id1 = t1.get_id();
	thread::id id2 = t2.get_id();
	thread::id id3 = t3.get_id();

	if (t1.joinable())
	{
		t1.join();
		cout << "t1 id=" << id1 << endl;
	}
	
	if (t2.joinable())
	{
		t2.join();
		cout << "t2 id=" << id2 << endl;
	}

	if (t3.joinable())
	{
		t3.join();
		cout << "t3 id=" << id3 << endl;
		for (int c = 0; c < myvector.size(); c++)
		{
			cout << myvector[c] << endl;
		}
	}    
	cout << "sum1=" << sum1 << "sum2=" << sum2 << endl;

	return 0;
}

