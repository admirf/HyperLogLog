#ifndef HYPER_LOG_LOG
#define HYPER_LOG_LOG

#include <bitset>

namespace HyperLogLog {
	typedef unsigned short ushort;

	constexpr auto M = 16384;
	constexpr auto REGISTER_SIZE = 6;

	class HyperLogLog {

	private:
		std::bitset<98304> registers;

	protected:
		ushort getIndex(const ushort&);
		ushort getValue(const ushort&);
		void setValue(const ushort&, const ushort&);
		std::bitset<REGISTER_SIZE> getRegister(const ushort&);

	public:
		HyperLogLog();
		~HyperLogLog();

		void test();
	};
}



#endif // !1


