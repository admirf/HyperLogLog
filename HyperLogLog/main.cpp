#include <iostream>
#include <string>
#include "HyperLogLog.h"

using namespace std;

int main()
{
	for (auto i = 1000; i < 100000; i += 1000) {
		hll::HyperLogLog hll(true, [i](double e) {
			string line = to_string(i) + ", " + to_string(e) + "\n";
			return line;
		});
		hll.test(i);
	}

	cout << "Finished..." << endl;

	cin.get();

	return 0;
}