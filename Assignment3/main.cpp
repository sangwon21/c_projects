#include <cassert>
#include "SmartStack.h"
#include "SmartQueue.h"
#include "QueueStack.h"
#include <iostream>
#include <limits.h>

using namespace std;
using namespace assignment3;

int main() 
{

	float a = static_cast<float>(static_cast<double>(3.4f) + static_cast<double>(1.2f) + static_cast<double>(4.6f) +
		static_cast<double>(3.32f) + static_cast<double>(10.2f) + static_cast<double>(1.1f) +
		static_cast<double>(-5.9f) + static_cast<double>(1.1f) + static_cast<double>(-12.4f) +
		static_cast<double>(9.2f));

	float d = static_cast<float>(static_cast<double>(9.2f) + static_cast<double>(-12.4f) + static_cast<double>(1.1f) + static_cast<double>(-5.9f)
		+ static_cast<double>(1.1f) + static_cast<double>(10.2f) + static_cast<double>(3.32f) + static_cast<double>(4.6f) +
		static_cast<double>(1.2f) + static_cast<double>(3.4f));
	float b = 3.4f + 1.2f + 4.6f + 3.32f + 10.2f + 1.1f + -5.9f + 1.1f + -12.4f + 9.2f;
	float c = 9.2f - 12.4f + 1.1f - 5.9f + 1.1f + 10.2f + 3.32f + 4.6f + 1.2f + 3.4f;
	SmartStack<float> ss;
	cout << "Max is : " << ss.GetMax() << endl;
	cout << "Min is : " << ss.GetMin() << endl;
	float er = 1.1f + 2.6f + 3.7f;
	float qwe = 2.6f + 1.1f - 1.1f;
	ss.Push(3.4f);
	ss.Push(1.2f);
	ss.Push(4.6f);
	ss.Push(3.32f);
	ss.Push(10.2f);
	ss.Push(1.1f);
	ss.Push(-5.9f);
	ss.Push(1.1f);
	ss.Push(-12.4f);
	ss.Push(9.2f);

	assert(ss.GetCount() == 10U);
	assert(ss.Peek() == 9.2f);
	assert(ss.GetMax() == 10.2f);
	assert(ss.GetMin() == -12.4f);
	cout << ss.GetSum() << endl;
	assert(ss.GetSum() == 15.8200026f);
	double av = ss.GetAverage();
	assert(ss.GetAverage() == 1.582);
	assert(ss.GetVariance() == 39.983);
	assert(ss.GetStandardDeviation() == 6.323);
	assert(ss.Peek() == 9.2f);
	assert(!ss.IsEmpty());

	float popped1 = ss.Pop();
	float popped2 = ss.Pop();
	ss.Pop();
	ss.Pop();
	ss.Pop();
	ss.Pop();
	ss.Pop();
	ss.Pop();
	ss.Pop();
	ss.Pop();
	assert(ss.IsEmpty());
	cout << ss.GetCount() << endl;
	cout << ss.GetSum() << endl;
	cout << "Max is : " << ss.GetMax() << endl;
	cout << "Min is : " << ss.GetMin() << endl;
	cout << "===================================================" << endl;
	ss.Push(1.0f);
	ss.Push(2.2f);
	ss.Push(2.2f);
	ss.Push(3.2f);
	ss.Push(3.2f);
	ss.Push(4.2f);
	ss.Pop();
	ss.Pop();

	cout << "Count is : " << ss.GetCount() << endl;
	cout << "Sum is : " << ss.GetSum() << endl;
	cout << "Max is : " << ss.GetMax() << endl;
	cout << "Min is : " << ss.GetMin() << endl;
	cout << "===================================================" << endl;


	cin.get();
	return 0;
}

