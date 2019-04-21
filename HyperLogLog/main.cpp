#include <iostream>
#include "HyperLogLog.h"

using namespace std;

int main()
{
	hll::HyperLogLog hll(true);
	hll.test();

	cin.get();

	return 0;
}