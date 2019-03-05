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
				sum += 1 / std::pow(2, value);
				++num;
			}
		}

		this->_count = (1 / sum) * this->util->alpha(num) * num * num;

		return this->_count;
	}

	void HyperLogLog::add(const void* element) {
		auto hash = std::bitset<64>(this->util->murmur64(element, 64));
		std::bitset<KEY_LENGTH> key;

		ushort i;
		ushort zeroes = 0;
		bool set = false;

		for (i = 0; i < KEY_LENGTH; ++i) key[i] = hash[i];
		for (; !set && i < 64; ++i, ++zeroes) set = hash[i];

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


	void HyperLogLog::test() {

#ifdef DEBUG
		std::map<std::string, bool> m;
		auto count = 0;

		for (auto k = 0; k < 10; ++k) {
			for (auto i = 0; i < 1000; ++i) {
				std::stringstream ss;
				ss << i;
				std::string out = ss.str();

				if (m.find(out) == m.end()) {
					m[out] = true;
					++count;
				}

				this->add(out.c_str());
			}
		}

		/*this->add("Element 2");
		this->add("Element 2");
		this->add("Element 1");
		this->add("test");
		this->add("fadgdgfrhsfdhdfgshsdfhsfdhsdhfdshfsdhsdhfdshfdshdfshsdfhfds");
		this->add("fadgdgfrhsfdhdfgshsdfhsfdhsdhfdshfsdhsdhfdshfdshdfshsdfhfds");
		this->add("Ultra divlji element koji bi trebo biti cudan");*/

		std::cout << count << std::endl;
		// this->count();
		std::cout << this->count() << std::endl;
#endif // DEBUG
		
	}
}


