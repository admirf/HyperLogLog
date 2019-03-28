#include "HyperLogLogUtil.h"
#include <ctime>
#include <cmath>
#include <cstdlib>

#define DEBUG

namespace hll {
	HyperLogLogUtil::HyperLogLogUtil() {
#ifdef DEBUG
		this->seed = 1996;
#else
		srand(static_cast<unsigned>(time(NULL)));
		this->seed = rand();
#endif
	}


	HyperLogLogUtil::~HyperLogLogUtil() {}

	double HyperLogLogUtil::linearCount(uint32_t m, uint32_t v) {
		auto _m = static_cast<double>(m);
		return _m * log(_m / v);
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


