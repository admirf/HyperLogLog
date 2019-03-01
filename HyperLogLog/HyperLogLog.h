#ifndef HYPER_LOG_LOG
#define HYPER_LOG_LOG

#include <bitset>

namespace HyperLogLog {

	typedef unsigned short uint;

	constexpr auto M = 16384;
	constexpr auto REGISTER_SIZE = 6;

	class HyperLogLog {

	private:
		std::bitset<98304> registers;

	protected:
		uint getIndex(const uint&);
		uint getValue(const uint&);
		void setValue(const uint&, const uint&);
		std::bitset<REGISTER_SIZE> getRegister(const uint&);

	public:
		HyperLogLog();
		~HyperLogLog();

		void test();
	};
}



#endif // !1


