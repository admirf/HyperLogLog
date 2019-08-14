#include "HyperLogLogUtil.h"
#include <ctime>
#include <cmath>
#include <chrono>
#include <cstdlib>
#include <cassert>
#include <iostream>
#define DEBUG

namespace hll {

	HyperLogLogUtil::HyperLogLogUtil(): rng(std::mt19937_64()), distribution(std::uniform_real_distribution<double>(0, 1)) {
		auto timeSeed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
		std::seed_seq ss{ uint32_t(timeSeed), uint32_t(timeSeed >> 32) };
		rng.seed(ss);

#ifdef DEBUG
		this->seed = 0;
#else
		this->seed = timeSeed;
#endif
	}


	HyperLogLogUtil::~HyperLogLogUtil() {}

	double HyperLogLogUtil::linearCount(uint32_t m, uint32_t v) {
		auto _m = static_cast<double>(m);
		return _m * log(_m / v);
	}

	double HyperLogLogUtil::empiricalApprox(double estimate, uint32_t M) {
		double square = M * M;
		auto scaler = (1 - (square - estimate) / square);
		return 0.9 + scaler;
	}

	int HyperLogLogUtil::zipf(double alfa, int n)
	{
		double c = this->normalizationConstant(alfa, n);
		double z = this->distribution(this->rng);
		double sum_prob;
		double zipf_value;

		sum_prob = 0;
		for (auto i = 1; i <= n; ++i) {
			sum_prob = sum_prob + c / pow((double) i, alfa);
			if (sum_prob >= z) {
				zipf_value = i;
				break;
			}
		}

		return static_cast<int>(zipf_value);
	}

	double HyperLogLogUtil::normalizationConstant(double alfa, int n)
	{
		double c = 0;
		for (auto i = 1; i <= n; ++i) {
			c = c + (1.0 / pow((double) i, alfa));
		}

		return 1.0 / c;
	}

	double HyperLogLogUtil::alpha(uint32_t m) {
		switch (m)
		{
		case 16:
			return 0.673;
		case 32:
			return 0.697;
		case 64:
			return 0.709;
		default:
			return 0.7213 / (1 + 1.079 / m);
		}
	}

	uint64_t HyperLogLogUtil::murmur64(const void * key, int len) {
		const uint64_t m = BIG_CONSTANT(0xc6a4a7935bd1e995);
		const int r = 47;
		const uint64_t seed = this->seed;

		uint64_t h = seed ^ (len * m);

		const uint64_t * data = (const uint64_t *)key;
		const uint64_t * end = data + (len / 8);

		while (data != end) {
			uint64_t k = *data++;

			k *= m;
			k ^= k >> r;
			k *= m;

			h ^= k;
			h *= m;
		}

		const unsigned char * data2 = (const unsigned char*) data;

		switch (len & 7) {
		case 7: h ^= uint64_t(data2[6]) << 48;
		case 6: h ^= uint64_t(data2[5]) << 40;
		case 5: h ^= uint64_t(data2[4]) << 32;
		case 4: h ^= uint64_t(data2[3]) << 24;
		case 3: h ^= uint64_t(data2[2]) << 16;
		case 2: h ^= uint64_t(data2[1]) << 8;
		case 1: h ^= uint64_t(data2[0]);
			h *= m;
		};

		h ^= h >> r;
		h *= m;
		h ^= h >> r;

		return h;
	}
}


