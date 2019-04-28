#include <iostream>
#include <fstream>
#include <string>
#include "HyperLogLog.h"

using namespace std;

int main()
{
	for (auto i = 1000; i < 10000; i += 200) {
		hll::HyperLogLog hll(true, [i](double e) {
			string line = to_string(i) + ", " + to_string(e) + "\n";
			return line;
		});
		hll.test(i);
	}

	cout << "Finished graph data..." << endl;

	ifstream csv;
	csv.open("categories.csv");

	if (!csv) {
		cout << "No file found...";
		return 1;
	}

	int item_count = 0;
	string word;
	hll::HyperLogLog hll;

	while (csv >> word) {
		hll.add(word.c_str());
		++item_count;
	}

	cout << "CSV count(" << item_count << "): " << hll.count() << endl;

	csv.close();

	cin.get();

	return 0;
}