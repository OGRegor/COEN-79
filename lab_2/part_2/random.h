// Gregor Limstrom COEN79 Lab 2 Part 2

#ifndef STATS_H
#define STATS_H
#include <iostream>

namespace coen79_lab2
{
	// This class implements a semi-random number generator that takes 4 paramaters, using the linear congrunce method
	class rand_gen
	{
		public:
			// Constructor for the class. Initializes everything to 0 or to parameters
			// Precondition: Called when the class is instanced
			// Postcondition: object is now instanced
			rand_gen(int seed = 0, int multiplier = 0, int increment = 0, int modulus = 0)
			{
				this->seed = seed;
				this->multiplier = multiplier;
				this->increment = increment;
				this->modulus = modulus;
			};

			// Fn: next
			// Desc: Generates a random number generator according to the algorithm given
			// Precondition: Must be called on an instanced class
			// Postcondition: returns the new seed and sets it as the next active seed
			int next();

			// Fn: set_seed
			// Desc: Sets the private variable
			// Precondition: object is instanced and seed is valid integer
			// Postcondition: seed variable is now changed
			void set_seed(int seed);

			// Fn: print_info
			// Desc: prints out variables in readable format
			// Precondition: object is instanced
			// Postcondition: values are printed
			void print_info() const;

		private:
			int seed;
			int multiplier;
			int increment;
			int modulus;
	};
}
#endif