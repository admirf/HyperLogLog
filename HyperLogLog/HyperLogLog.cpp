#include "HyperLogLog.h"
#include <iostream>

namespace HyperLogLog {

	HyperLogLog::HyperLogLog()
	{
	}


	HyperLogLog::~HyperLogLog()
	{
	}


	uint HyperLogLog::getIndex(const uint& index) {
		return index * REGISTER_SIZE;
	}


	std::bitset<REGISTER_SIZE> HyperLogLog::getRegister(const uint& index) {
		auto base_index = this->getIndex(index);
		std::bitset<REGISTER_SIZE> slice;

		for (int i = 0; i < REGISTER_SIZE; ++i) {
			slice[i] = this->registers[base_index + i];
		}

		return slice;
	}


	void HyperLogLog::setValue(const uint& index, const uint& value) {
		auto base_index = this->getIndex(index);
		std::bitset<REGISTER_SIZE> bitvalue(value);

		for (int i = 0; i < REGISTER_SIZE; ++i) {
			this->registers[base_index + i] = bitvalue[i];
		}
	}

	
	uint HyperLogLog::getValue(const uint& index) {
		return this->getRegister(index).to_ulong();
	}


	void HyperLogLog::test() {
		this->setValue(4, 3);

		std::cout << this->getRegister(4).to_string() << std::endl;
	}
}


