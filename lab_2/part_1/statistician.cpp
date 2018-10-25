// SEE statistician.h FOR DOCUMENTATION

#include <cassert>
#include <iostream>
#include "statistician.h"

using namespace std;
using namespace coen79_lab1;
namespace coen79_lab1
{
	void statistician::next(const double& input)
	{
		this->length++;
		this->sum += input;
		this->mean = sum/length;
		if(input < minimum || !this->minimum) this->minimum = input;
		if(input > maximum || !this->maximum) this->maximum = input;
	};

	void statistician::reset()
	{
		this->length = 0;
		this->sum = 0;
		this->mean = 0;
		this->minimum = 0;
		this->maximum = 0;
	};
	
	statistician operator +(const statistician& s1, const statistician& s2)
	{
		statistician tmp;
		tmp.length += s1.get_length();
		tmp.length += s2.get_length();
		tmp.sum += s1.get_sum();
		tmp.sum += s2.get_sum();
		tmp.mean = tmp.sum / tmp.length;
		tmp.minimum = std::min(s1.minimum, s2.minimum);
		tmp.maximum = std::max(s1.maximum, s2.maximum);
		return tmp;
	};

	statistician operator *(const double& scale, const statistician& s)
	{
		statistician tmp;
		// If the scale is 0, returns a blank statistician to save time
		if(!scale) return tmp;

		tmp.sum = s.sum;
		tmp.length = s.length;
		tmp.sum *= scale;
		tmp.mean = tmp.sum / tmp.length;
		if(scale < 0)
		{
			tmp.minimum = s.maximum; 
			tmp.minimum *= scale;
			tmp.maximum = s.minimum; 
			tmp.maximum *= scale;
		}
		else
		{
			tmp.minimum = s.minimum;
			tmp.minimum *= scale;
			tmp.maximum = s.maximum; 
			tmp.maximum *= scale;
		}
		return tmp;
	};

	bool operator ==(const statistician& s1, const statistician& s2)
	{
		if(s1.get_length() == 0 && s2.get_length() == 0) return true;
		if(s1.get_length() == s2.get_length() &&
			s1.get_sum() == s2.get_sum() &&
			s1.get_mean() == s2.get_mean() &&
			s1.get_minimum() == s2.get_minimum() &&
			s1.get_maximum() == s2.get_maximum()) return true;
		return false;
	};
}