//@	{"targets":[{"name":"gatesequence_test","type":"application"}]}

#include "gatesequence.hpp"
#include "../common/blob.hpp"

BLOB(dance_000,"patterns/dance_000.txt");

int main()
	{
	Happychords::GateSequence s(reinterpret_cast<const int8_t*>(dance_000_begin)
		,reinterpret_cast<const int8_t*>(dance_000_end));

	return 0;
	}