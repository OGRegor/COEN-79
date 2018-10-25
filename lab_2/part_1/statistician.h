#ifndef STATS_H
#define STATS_H
#include <iostream>

namespace coen79_lab1
{
	// This class creates a dataset that keeps statistics on a sequence of numbers
	class statistician
	{
		public:
			// Constructor
			// Precondition: Called when the object is called, paramaters must be of valid type
			// Postcondition: 
			statistician(int length = 0, double sum = 0.0, double mean = 0.0, double minimum = 0.0, double maximum = 0.0)
			{
				this->length = length;
				this->sum = sum;
				this->mean = mean;
				this->minimum = minimum;
				this->maximum = maximum; 
			};

			// Fn: next
			// Desc: adds a number to the sequence and does the corresponding calculations
			// Pre: sequence must be instanced, input is valid double
			// Post: sequence statistics are updated with the new value
			void next(const double& input);

			// Fn: get_length
			// Desc: returns length
			// Pre: obj is instanced
			// Post: length is returned
			int get_length() const
			{
				return length;
			};

			// Fn: get_sum
			// Desc: returns sum
			// Pre: obj is instanced
			// Post: returns the sum
			double get_sum() const
			{
				return sum;
			};

			// Fn: get_minimum
			// Desc: returns mean
			// Pre: obj is instanced and has at least one entry
			// Post: returns the mean		
			double get_mean() const
			{
				if(!length) return 0;
				return mean;
			};

			// Fn: get_minimum
			// Desc: returns the min
			// Pre: obj is instanced and has at least one entry
			// Post: returns the min
			double get_minimum() const
			{
				if(!length) return 0;
				return minimum;
			};

			// Fn: get_maximum
			// Desc: returns max
			// Pre: obj is instanced and has at least one entry
			// Post: returns the max
			double get_maximum() const
			{
				if(!length) return 0;
				return maximum;
			}

			// Fn: reset
			// Desc: resets the sequence, allowing for reuse of the object
			// Pre: obj is instanced
			// Post: all values are reset to base values
			void reset();

			// NON-MEMBER functions for the statistician class:
			// FRIENDS - Allows the operators to access private variables as nonmember functions

			// Precondition: s1 and s2 must be valid statisticians
			// Postcondition: The statistician that is returned contains all the
			// numbers of the sequences of s1 and s2.
			friend statistician operator +(const statistician& s1, const statistician& s2);

			// Precondition: Scale is valid, and s is valid.
			// Postcondition: The statistician that is returned contains the same
			// numbers that s does, but each number has been multiplied by the
			// scale number.
			friend statistician operator *(const double& scale, const statistician& s);

			// Precondition: s1 and s2 are existing objects
			// Postcondition: The return value is true if s1 and s2 have the zero//
			// length. Also, if the length is greater than zero, then s1 and s2 must//
			// have the same length, the samemean, the same minimum,//
			// the same maximum, and the same sum.
			friend bool operator ==(const statistician& s1, const statistician& s2);

		private:
			// Per the lab instructions, do not store the sequence, just the needed stats on it
			int length;
			double sum;
			double mean;
			double minimum;
			double maximum;
	};
}
#endif