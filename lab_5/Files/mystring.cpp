/*
	File:
		mystring.cpp
	
	Author:
		Gregor Limstrom
	
	Purpose:
		Implement a custom string class for Lab 5 of COEN79

	Invariants:
		The string is stored in a null terminated character array, characters. The size can be dynamically sized through each function, but 
		this is inneficient, so the reserve function can be used to lessen the number of copies needed to be made.

		Allocated represents the total size of memory that the character array is allocated to. This is reassigned
		whenever the array is expanded or contracted.

		Current_length represents the total number of characters used from the allocated memory. The null terminating 
		character can always be found at characters[current_length]
*/

#include "mystring.h"

namespace coen79_lab5
{
    string::string(const char str[])
    {
    	assert(is_null_terminated(str));
		characters = new char [arr_size(str)];
		allocated = arr_size(str);
    	for(size_t i = 0; i < arr_size(str); i++)
    	{
    		characters[i] = str[i];
    	}
    	*(characters + arr_size(str)) = '\0';
    	current_length = arr_size(str) - 1;
    };

    string::string(char c)
    {
    	characters = new char [2];
    	allocated = 2; 		
    	characters[0] = c;
    	characters[1] = '\0';
    	current_length = 1;
    };

    string::string(const string& source)
    {
		characters = new char [source.length() + 1];
		allocated = source.length() + 1;
		for(size_t i = 0; i <= source.length(); i++)
    	{
    		characters[i] = source[i];
    	};
    	current_length = source.length();
    };

    string::~string()
    {
    	delete [] characters;
    };
    
    void string::operator +=(const string& addend)
    {

    	if(current_length + addend.length() + 1 > allocated)
    	{

	    	if(allocated) 
    		{
    			char * tmp = characters;
	    		characters = new char [current_length + addend.length() + 1];
	    		allocated = current_length + addend.length() + 1;
	    		for(size_t i = 0; i < current_length + addend.length(); i++)
    			{
    				characters[i] = tmp[i];
    			}
    			delete [] tmp;
    		} else
    		{
	    		characters = new char [current_length + addend.length() + 1];
	    		allocated = current_length + addend.length() + 1;
    		};
    	};
    	this->insert(addend, current_length);
    };

    void string::operator +=(const char addend[])
    {
    	string tmp = string(addend);
    	*this += tmp;
    };

    void string::operator +=(char addend)
    {
    	string tmp = string(addend);
    	*this += tmp;
    };

    void string::reserve(size_t n)
    {
    	characters = new char [n];
    	allocated = n;
    };

    void string::operator=(const string& source)
    {
    	if(source.length() + 1 > allocated)
    	{
    		delete [] characters;
    		characters = new char [source.length() + 1];
    		allocated = source.length() +1;
    	};
    	for(size_t i = 0; i <= source.length(); i++)
    	{
    		*(characters + i) = source[i];
    	};
    	current_length = source.length();
    };

    void string::insert(const string& source, unsigned int position)
    {
    	assert(position <= current_length);
    	string tmp = source;
    	for(size_t i = position; i < current_length; i++)
    	{
    		tmp += *(characters + i);
    	};
    	current_length += source.length();
    	size_t i = position;
    	for(size_t j = 0; j < tmp.length(); j++)
    	{
    		characters[i++] = tmp[j];
    	};

    };

    void string::dlt(unsigned int position, unsigned int num)
    {
    	assert(position + num <= current_length);
    	if(position + num == current_length)
    	{
    		// delet to end case	
    		current_length -= num;
    		characters[current_length] = '\0';
    	} 
    	else
    	{
    		string tmp;
    		for(size_t i = position + num; i < current_length; i++)
    		{
    			tmp += characters[i];
    		}
    		size_t j = 0;
    		current_length -= num;
    		for(size_t i = position; i < current_length; i++)
    		{
    			characters[i] = tmp[j++];
    		}
    		characters[current_length] = '\0';
    	}
    };

    void string::replace(char c, unsigned int position)
    {
		assert(position < current_length);
		*(characters + position) = c;
    };

    void string::replace(const string& source, unsigned int position)
    {
    	assert(position + source.length() <= current_length);
    	size_t j = 0;
    	for(size_t i = position; i < position + source.length(); i++)
    	{
    		*(characters + i) = source[j++];
    	};

    };
    
    char string::operator[](size_t position) const
    {
    	assert(position <= current_length);
		return characters[position];
    };
    
    int string::search(char c) const
    {
    	for (size_t i = 0; i < current_length; i++)
    	{
    		if(*(characters + i) == c) return i;
    	};
    	return -1;
    };
    
    int string::search(const string& substring) const
    {
    	for (size_t i = 0; i < current_length; i++)
    	{
    		if(*(characters + i) == substring[0])
    		{
    			bool flag = 1;
    			for(size_t j = 0; j < substring.length(); j++)
    			{
    				if(*(characters + i + j) != substring[j]) flag = 0;
    			};
    			if(flag) return i;
    		};
    	};
    	return -1;
    };

    unsigned int string::count(char c) const
    {
    	unsigned int count = 0;
    	for(size_t i = 0; i < current_length; i++)
    	{
    		if(*(characters + i) == c) count++;
    	}
    	return count;
    };
    
    std::ostream& operator <<(std::ostream& outs, const string& source)
    {
    	for(size_t i = 0; i < source.length(); i++)
    	{
    		outs << source[i];
    	};
    	return outs;
    };
    
    bool operator ==(const string& s1, const string& s2)
    {
    	if(s1.length() == s2.length())
    	{
    		for(size_t i = 0; i < s1.length(); i++)
    		{
    			if(s1[i] != s2[i]) return 0;
    		};
    		return 1;
    	};
    	return 0;
    };
    
    bool operator !=(const string& s1, const string& s2)
    {
    	return !(s1 == s2);
    };

    bool operator > (const string& s1, const string& s2)
    {
    	for(size_t i = 0; i < (s1.length() < s2.length() ? s1.length() : s2.length()); i++)
    	{
    		if(s1[i] < s2[i]) return 0;
    		if(s1[i] > s2[i]) return 1;
    	};
    	return 0;
    };
    
    bool operator < (const string& s1, const string& s2)
    {
    	return s2 > s1;
    };
    
    bool operator >=(const string& s1, const string& s2)
    {
    	return (s1 == s2) || (s1 > s2);
    };
    
    bool operator <=(const string& s1, const string& s2)
    {
    	return (s1 == s2) || (s1 < s2);
    };

    string operator+(const string &s1, const string& s2)
    {
    	string tmp;
    	tmp += s1;
    	tmp += s2;
    	return tmp;
    };

    string operator+(const string& s1, const char addend[])
    {
    	string tmp;
    	tmp += s1;
    	tmp += addend;
    	return tmp;
    };

    std::istream& operator >> (std::istream& ins, string& target)
    {
    	char *tmp = new char[1000];
    	ins >> tmp;
    	target = string(tmp);
    	return ins;
    };

	size_t arr_size(const char* arr)
	{
		size_t count = 0;
		for(size_t i = 0; i < 1000; i++) 
		{
			count++; 
			if(arr[i] == '\0') break;
		};
		return count;
	};

	bool is_null_terminated(const char* arr)
	{
		for(size_t i = 0; i < arr_size(arr); i++) if(arr[i] == '\0') return 1;				
		return 0;
	};
}