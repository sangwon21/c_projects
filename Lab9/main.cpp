#include <cassert>
#include "IceCube.h"
#include "ObjectPool.h"
#include "Game.h"
#include <iostream>

using namespace lab9;
using namespace std;

int main()
{
	ObjectPool<IceCube> op(20);
	assert(0 == op.GetFreeObjectCount()); // 0�� ��ȯ

	IceCube* i1 = op.Get();
	IceCube* i2 = op.Get();

	assert(0 == op.GetFreeObjectCount()); // 0�� ��ȯ

	op.Return(i1);
	assert(1 == op.GetFreeObjectCount()); // 1�� ��ȯ

	op.Return(i2);
	assert(2 == op.GetFreeObjectCount()); // 2�� ��ȯ

	cout << "End of the Test" << endl;
	cin.get();
	return 0;
}