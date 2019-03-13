#ifndef HYPER_LOG_LOG
#define HYPER_LOG_LOG

#include "HyperLogLogUtil.h"
#include <bitset>

namespace hll {
	typedef unsigned short ushort;

	constexpr auto M = 8;
	constexpr auto REGISTER_SIZE = 6;
	constexpr auto KEY_LENGTH = 3;

	class HyperLogLog {

	private:
		std::bitset<M * REGISTER_SIZE> registers;
		std::unique_ptr<HyperLogLogUtil> util;
		double _count;

	protected:
		ushort getIndex(const ushort&);
		ushort getValue(const ushort&);
		void setValue(const ushort&, const ushort&);
		std::bitset<REGISTER_SIZE> getRegister(const ushort&);
		void printRegisters();

	public:
		HyperLogLog();
		~HyperLogLog();

		void add(const void*);
		double count();

		void test();
	};
}



#endif // !1


