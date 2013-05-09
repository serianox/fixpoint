
#include <cstdlib>
#include <iostream>
#include <iomanip>

#include "fixpoint.hpp"

template<typename T>
inline void pp(T what)
{
	std::cout << "0x" << std::setw(8) << std::setfill('0') << std::hex << what.value_ << std::dec << " : " << what << std::endl;
}

int main(int argc, char * argv[])
{
	(void) argc, (void) argv;

	fx7_8_t foo =  3.1_fx;
	fx3_4_t bar = -3.1_fx;
	pp(foo);
	pp(bar);
	pp(foo + bar);
	pp(foo - bar);

	return EXIT_SUCCESS;
}
