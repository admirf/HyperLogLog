#ifndef HYPER_LOG_LOG_UTIL
#define HYPER_LOG_LOG_UTIL
#define BIG_CONSTANT(x) (x)

#include <cstdint>

namespace hll {
	class HyperLogLogUtil
	{
	private:
		uint64_t seed = 0;
	public:
		HyperLogLogUtil();
		~HyperLogLogUtil();

		uint64_t murmur64(const void*, int);
	};
}



#endif

