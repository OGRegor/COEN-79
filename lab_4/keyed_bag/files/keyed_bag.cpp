/*
	COEN79 Lab 4 Part 1
	Gregor Limstrom
	Fri 215-5 Lab
	Benham Dezfouli
*/
#include "keyed_bag.h"

using namespace std;
using namespace coen79_lab4;

/*
	Invariants of class:

	keys: Holds an array of keys of key_type that correspond in index to the value in values.
	values: Holds an array of values that are only searchable by key
	used: denotes how many spots are taken in the arrays, max is at capacity. used to check
			validity of bounds.

*/

namespace coen79_lab4
{
	keyed_bag::keyed_bag()
	{
		used = 0;
	};

	void keyed_bag::erase()
	{
		for(size_type i = 0; i < used; i++)
		{
			keys[i] = "";
			values[i] = 0;
		}
		used = 0;
	};

	bool keyed_bag::erase(const key_type& key)
	{
		for(size_type i = 0; i < used; i++)
		{
			if(keys[i] == key)
			{
				for(size_type j = i; j < used - 1; j++)
				{
					keys[j] = keys[j + 1];
					values[j] = values[j + 1];
				}
				used--;
				return 1;
			}
		}
		return 0;
	};

	void keyed_bag::insert(const value_type& entry, const key_type& key)
	{
		assert(size() < CAPACITY && !has_key(key));
		keys[used] = key;
		values[used++] = entry;
	};

	void keyed_bag::operator +=(const keyed_bag& addend)
	{
		assert(size() + addend.size() <= CAPACITY && !hasDuplicateKey(addend));
		size_type size = addend.size();
		for(size_type i = 0; i < size; i++)
		{
			insert(addend.values[i], addend.keys[i]);
		};
	};

	bool keyed_bag::has_key(const key_type& key) const
	{
		for(size_type i = 0; i < used; i++)
		{
			if(keys[i] == key) return 1;
		}
		return 0;
	};

	keyed_bag::value_type keyed_bag::get(const key_type& key) const
	{
		assert(has_key(key));
		size_type i;
		for(i = 0; i < used; i++)
		{
			if(key == keys[i]) break;
		};
		return values[i];
	};

	keyed_bag::size_type keyed_bag::size() const
	{
		return used;
	};

	keyed_bag::size_type keyed_bag::count(const value_type& target) const
	{
		size_type count = 0;
		for(size_type i = 0; i < used; i++)
		{
			if(values[i] == target) count++;
		};
		return count;
	};

	bool keyed_bag::hasDuplicateKey(const keyed_bag& otherBag) const
	{
		for(size_type i = 0; i < used; i++)
		{
			if(otherBag.has_key(keys[i])) return 1;
		}
		return 0;
	};

    keyed_bag operator +(const keyed_bag& b1, const keyed_bag& b2)
    {
    	assert(b1.size() + b2.size() < keyed_bag::CAPACITY && !b1.hasDuplicateKey(b2));
    	keyed_bag tmp;
    	tmp += b1;
    	tmp += b2;
    	return tmp;
    };
};