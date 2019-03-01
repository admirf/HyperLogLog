#ifndef HYPER_LOG_LOG_UTIL
#define HYPER_LOG_LOG_UTIL

#include <string>

namespace HyperLogLog {
	class HyperLogLogUtil
	{
	public:
		HyperLogLogUtil();
		~HyperLogLogUtil();
		static uint32_t murmur64(const std::string&);
	};
}



#endif

