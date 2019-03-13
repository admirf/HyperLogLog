#include "HyperLogLog.h"

#define DEBUG
#ifdef DEBUG

#include <Windows.h>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <cmath>
#include <map>

#endif // DEBUG

namespace hll {

	HyperLogLog::HyperLogLog() : util(std::make_unique<HyperLogLogUtil>()), _count(0) {}


	HyperLogLog::~HyperLogLog() {}

	double HyperLogLog::count() {
		if (this->_count) {
			return this->_count;
		}

		uint32_t num = 0;
		double sum = 0;

		for (auto i = 0; i < M; ++i) {
			auto value = this->getValue(i);

			if (value) {
				sum += 1 / pow(2, value);
				++num;
			}
		}

		this->_count = (1 / sum) * this->util->alpha(num) * num * num;

		return this->_count;
	}

	void HyperLogLog::add(const void* element) {
		auto hash = std::bitset<64>(this->util->murmur64(element, 64));

#ifdef DEBUG
		std::cout << "Hash entry: " << std::endl;
		std::cout << hash << std::endl;
#endif

		std::bitset<KEY_LENGTH> key;

		ushort i;
		ushort zeroes = 0;
		bool set = false;

		for (i = 0; i < KEY_LENGTH; ++i) key[i] = hash[i];
		for (; !set && i < 64; ++i, ++zeroes) set = hash[i];

#ifdef DEBUG
		std::cout << "Zeroes: " << zeroes << std::endl;
#endif

		ushort index = static_cast<ushort>(key.to_ulong());
		ushort currValue = this->getValue(index);

		if (zeroes > currValue) {
			this->setValue(index, zeroes);
			this->_count = 0;
		}
	}


	ushort HyperLogLog::getIndex(const ushort& index) {
		return index * REGISTER_SIZE;
	}


	std::bitset<REGISTER_SIZE> HyperLogLog::getRegister(const ushort& index) {
		auto base_index = this->getIndex(index);
		std::bitset<REGISTER_SIZE> slice;

		for (int i = 0; i < REGISTER_SIZE; ++i) {
			slice[i] = this->registers[base_index + i];
		}

		return slice;
	}


	void HyperLogLog::setValue(const ushort& index, const ushort& value) {
		auto base_index = this->getIndex(index);
		std::bitset<REGISTER_SIZE> bitvalue(value);

		for (int i = 0; i < REGISTER_SIZE; ++i) {
			this->registers[base_index + i] = bitvalue[i];
		}
	}

	
	ushort HyperLogLog::getValue(const ushort& index) {
		return static_cast<ushort>(this->getRegister(index).to_ulong());
	}


	void HyperLogLog::printRegisters() {
		for (int i = 0; i < M; ++i) {
			if (i % REGISTER_SIZE == 0) std::cout << std::endl;

			std::cout << this->registers[i];
		}
	}


	void HyperLogLog::test() {

#ifdef DEBUG

		// data set 1 = 10
		this->add("Element 2");
		this->add("Element 2");
		this->add("Element 1");
		this->add("test");
		this->add("fadgdgfrhsfdhdfgshsdfhsfdhsdhfdshfsdhsdhfdshfdshdfshsdfhfds");
		this->add("fadgdgfrhsfdhdfgshsdfhsfdhsdhfdshfsdhsdhfdshfdshdfshsdfhfds");
		this->add("Ultra divlji element koji bi trebo biti cudan");
		this->add("Admir je lijen.");
		this->add("Admir nije lijen.");
		this->add("Tatar > Ronaldo");
		this->add("Testing on small sets");
		this->add("Hope this works.");

		// data set 2 = 5
		this->add("Nedret treba bit fitnes vloger");
		this->add("Mechovi su op u auto chessu early game");
		this->add("127.0.0.1:8000");
		this->add("192.168.0.1");
		this->add("localhost:8000");

		std::cout << "Count: " << std::endl;
		std::cout << this->count() << std::endl;
		this->printRegisters();
#endif // DEBUG
		
	}
}


