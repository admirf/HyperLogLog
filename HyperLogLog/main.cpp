#include <iostream>
#include <fstream>
#include <string>
#include "HyperLogLog.h"

using namespace std;

int main(int argn, char** args)
{
	string csv_filename = "data.csv";
	if (argn > 1) {
		csv_filename = args[1];
	}

	/*for (auto i = 1000; i < 100000; i += 1000) {
		hll::HyperLogLog hll(true, [i](double e) {
			string line = to_string(i) + ", " + to_string(e) + "\n";
			return line;
		});
		hll.test(i);
	}

	cout << "Finished graph data..." << endl;*/

	ifstream csv;
	csv.open(csv_filename);

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

	cout << hll.count() << endl;

	csv.close();

	return 0;
}