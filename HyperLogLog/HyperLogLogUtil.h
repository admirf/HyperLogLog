#ifndef HYPER_LOG_LOG_UTIL
#define HYPER_LOG_LOG_UTIL
#define BIG_CONSTANT(x) (x)

#include <cstdint>
#include <random>
#include <chrono>
#include <memory>

namespace hll {
	class HyperLogLogUtil
	{
	private:
		uint64_t seed = 0;
		std::mt19937_64 rng;
		std::uniform_real_distribution<double> distribution;
	protected:
		double normalizationConstant(double, int);
	public:
		HyperLogLogUtil();
		~HyperLogLogUtil();

		uint64_t murmur64(const void*, int);
		double alpha(uint32_t);
		double linearCount(uint32_t, uint32_t);
		double empiricalApprox(double, uint32_t);
		int zipf(double, int);
	};
}



#endif

