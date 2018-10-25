// FOR DOCUMENTATION SEE HEADER FILE: random.h

#include <cassert>
#include <iostream>
#include "random.h"
using namespace std;
using namespace coen79_lab2;
namespace coen79_lab2
{
	int rand_gen::next()
	{
		int mod =  (multiplier * seed + increment) % modulus;
		set_seed(mod);
		return mod;
	};

	void rand_gen::set_seed(int seed)
	{
		this->seed = seed;
	};

	void rand_gen::print_info() const
	{
		cout << "seed:" << seed << endl;
		cout << "multiplier:" <<multiplier << endl;
		cout << "increment:" << increment << endl;
		cout << "modulus:" << modulus << endl;
	}
}