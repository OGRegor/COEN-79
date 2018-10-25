/*
	File: sequence1.cpp
	Author: Gregor Limstrom, COEN79 Fri 215
	Purpose: Implement a sequence class with the assigned methods
*/

/*
	Invariants:
	index is used to keep track of where the user is looking. 
		It can never be less than 0, or greater than or equal to capacitance. 
		It is used to fetch items from the sequence, and is modified with start, end, and last,
		and also all the functions that change it.

	used counts the number of the items in the list. it is used to catch boundary cases where we are 
		trying to find items bigger than the amount used, and to iterate through the loop.

	data is the array where the items are stored. it is size capacitance, and type type_value.
*/

#include "sequence1.h"
#include <iostream>
#include <cmath>
#include <cassert>

using namespace std;
using namespace coen79_lab3;

namespace coen79_lab3
{
	void sequence::start()
	{
		index = 0;
	};

	void sequence::end()
	{
		index = used - 1;
	};

	void sequence::last()
	{
		index = sequence::CAPACITY - 1;
	};

	sequence::value_type sequence::current() const
	{
		assert(is_item());
		return data[index];
	};

	void sequence::advance()
	{
		assert(is_item());
		if(index < CAPACITY - 1)
		{
			index ++;
			return;
		}
	};

	void sequence::retreat()
	{
		if(index)
		{
			index--;
			return;
		}
	};

	void sequence::insert(const value_type& entry)
	{
		assert(used < sequence::CAPACITY);
		if(!data[index])
		{
			data[index] = entry;
			used++;
			return;
		}

		value_type prev;
		value_type to_insert = entry;
		for(size_type i = index; i < used; i++)
		{
			prev = data[i];
			data[i] = to_insert;
			to_insert = prev;
		}
		used++;
		data[used] = to_insert;
	};

	void sequence::attach(const value_type& entry)
	{
		assert(used < sequence::CAPACITY);
		if(!data[index])
		{
			data[used] = entry;
			used++;
			return;
		};

		value_type prev;
		value_type to_insert = entry;
		for(size_type i = index + 1; i < used; i++)
		{
			prev = data[i];
			data[i] = to_insert;
			to_insert = prev;
		}
		index = used;
		used++;
		data[used] = to_insert;
	};

	void sequence::remove_current()
	{
		assert(is_item());
		size_type i = 0;
		for(int i = index; i < used; i++) data[i] = data[i+1];
		used--;
	};

	void sequence::insert_front(const value_type& entry)
	{
		assert(used < sequence::CAPACITY);

		if(!used)
		{
			data[0] = entry;
			used++;
			index = 0;
			return;
		}

		value_type prev;
		value_type to_insert = entry;
		for(size_type i = 0; i < used; i++)
		{
			prev = data[i];
			data[i] = to_insert;
			to_insert = prev;
		}
		data[used] = to_insert;
		used++;
		index = 0;
	};

	void sequence::attach_back(const value_type& entry)
	{
		assert(used < sequence::CAPACITY);
		data[used++] = entry;
		index = used;
	};

	void sequence::remove_front()
	{
		assert(is_item());
		for(size_type i = 0; i < used; i++) data[i] = data[i + 1];
		used--;
		index = 0;

	};

	void sequence::operator +=(const sequence& rhs)
	{
		assert((rhs.size() + used) < CAPACITY);
		for(size_type i = 0; i < rhs.size(); i++) data[used++] = rhs.data[i];
	};

	sequence operator +(const sequence& lhs, const sequence& rhs)
	{
		assert(lhs.size() + rhs.size() < sequence::CAPACITY);
		sequence tmp;
		tmp += lhs;
		tmp += rhs;
		tmp.start();
		return tmp;
	}

	sequence::size_type sequence::size() const
	{
		return used;
	};

	bool sequence::is_item() const
	{
		if(data[index]) return true;
		return false;
	};


		return data[index];
	};

	sequence::value_type sequence::mean() const
	{
		double sum;
		for(size_type i = 0; i < used; i++) sum += data[i];
		return sum / used;
	};

	sequence::value_type sequence::standardDeviation() const
	{
		double mean = this->mean();
		double stddev;
		for(size_type i = 0; i < used; i++) stddev += pow(data[i] - mean, 2);
		return sqrt(stddev);
	};

	double summation(sequence& seq)
	{
		double sum;
		for(int i = 0; i < seq.size(); i++) 
		{ 
			sum += seq[i];
		}		
		return sum;
	};
}

