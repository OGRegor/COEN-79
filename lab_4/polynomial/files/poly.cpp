/*
	Polynomial Class implementation with an array
	Gregor Limstrom
	Lab 4 part 2
*/
#include "poly.h"

/*
	Invariants:
		MAXIMUM_DEGREE: Max degree of the polynomial, one less than array size. Used
			to check validity of operations

		current_degree: stores the current max degree of the polynomial, used to make 
			some calculations faster without the need for a loop.

		poly[]: array used to store the polynomial. The index is the power that x is
			raised to i.e. [1,2,3] = 1 + 2x + 3x^2. Max size is capped at MAXIMUM_DEGREE
			 + 1
*/

using namespace std;
using namespace coen79_lab4;

namespace coen79_lab4
{
	polynomial::polynomial(double c, unsigned int exponent)
	{
		assert(exponent <= MAXIMUM_DEGREE);
		clear();
		current_degree = exponent;
		poly[exponent] = c;
	};

	void polynomial::update_current_degree()
	{
		unsigned int i;
		for(i = MAXIMUM_DEGREE; i > 0; i--)
		{
			if(poly[i] != 0.0) break;
		};
		current_degree = i;
	};

  	void polynomial::assign_coef(double c, unsigned int exponent)
  	{
  		assert(exponent <= MAXIMUM_DEGREE);
  		poly[exponent] = c;
 		update_current_degree();
  	};

  	void polynomial::add_to_coef(double amount, unsigned int exponent)
  	{
  		assert(exponent <= MAXIMUM_DEGREE);
  		poly[exponent] += amount;
  		update_current_degree();
  	};

	void polynomial::clear()
	{
		for(unsigned int i = 0; i < MAXIMUM_DEGREE + 1; i++) poly[i] = 0.0;
		update_current_degree();
	};

	polynomial polynomial::antiderivative() const
	{
		assert(degree() <= MAXIMUM_DEGREE);
		polynomial tmp;
		for(unsigned int i = 0; i <= current_degree; i++)
		{
			tmp.assign_coef(coefficient(i) * pow(i + 1, -1), i + 1);
		};
		return tmp;
	};

    double polynomial::coefficient(unsigned int exponent) const
    {
    	return poly[exponent];
    };

    double polynomial::definite_integral(double x0, double x1) const
    {
    	return this->antiderivative()(x1) - this->antiderivative()(x0);
    };

    unsigned int polynomial::degree() const
    {
    	return current_degree;
    };
    
    polynomial polynomial::derivative() const
    {
		assert(degree() < MAXIMUM_DEGREE);
		polynomial tmp;
		for(unsigned int i = 0; i < current_degree;)
		{
			tmp.add_to_coef(this->coefficient(++i) * i, i - 1);
		};
		tmp.update_current_degree();
		return tmp;
    };
    
    double polynomial::eval(double x) const
    {
    	double sum = 0.0;
    	for(unsigned int i = 0; i <= current_degree; i++)
    	{
    		sum += poly[i] * pow(x, i);
    	};
    	return sum;
    };
    
    bool polynomial::is_zero() const
    {
    	return (current_degree == 0 && poly[0] == 0);
    };
    
    unsigned int polynomial::next_term(unsigned int e) const
    {
    	for(unsigned int i = e; i < MAXIMUM_DEGREE; i++)
    	{
    		if(poly[i]) return i;
    	};
    	return 0;
    };
	
	unsigned int polynomial::previous_term(unsigned int e) const
	{
		unsigned int i;
		if(e == 0) return UINT_MAX;
		for(i = e - 1; i > 0; i--)
		{
			if(poly[i]) break;
		};
		return i;
	};

  	double polynomial::operator() (double x) const
  	{
  		return eval(x);
  	};

    polynomial operator +(const polynomial& p1, const polynomial& p2)
    {
    	polynomial tmp;
    	for(unsigned int i = 0; i < polynomial::MAXIMUM_DEGREE + 1; i++)
    	{
    		tmp.add_to_coef(p1.coefficient(i), i);
    		tmp.add_to_coef(p2.coefficient(i), i);
    	};
    	tmp.update_current_degree();
    	return tmp;
    };

    polynomial operator -(const polynomial& p1, const polynomial& p2)
    {
    	polynomial tmp;
    	for(unsigned int i = 0; i < polynomial::MAXIMUM_DEGREE + 1; i++)
    	{
    		tmp.add_to_coef(p1.coefficient(i), i);
    		tmp.add_to_coef(-1 * p2.coefficient(i), i);
    	};
    	tmp.update_current_degree();
    	return tmp;
    };

    polynomial operator *(const polynomial& p1, const polynomial& p2)
    {
    	polynomial tmp;
    	unsigned int i = p1.degree(),  j = p2.degree();
    	while(i != UINT_MAX)
    	{
    		j = p2.degree();
    		while(j != UINT_MAX)
    		{
    			tmp.add_to_coef(p1.coefficient(i) * p2.coefficient(j), i + j);
    			j = p2.previous_term(j);
    		};
    		i = p1.previous_term(i);
    	}
    	return tmp;
    };

    std::ostream& operator << (std::ostream& out, const polynomial& p)
    {
    	unsigned int i = p.degree();
    	while(i > 0)
    	{
    		switch (i)
    		{
    			case 1:
    				if(p.degree() == 1)
    				{
    					out << p.coefficient(1) << "x";	
    					break;
    				}
    				(p.coefficient(i) > 0) ? (out << "+ ") : (out << "- ");
    				out << abs(p.coefficient(i)) << "x ";
    				break;

    			default:
    				if(i == p.degree())
    				{
    					out << p.coefficient(i) << "x^" << i << " ";
    					break;
    				} else {
	    				(p.coefficient(i) > 0) ? (out << "+ ") : (out << "- ");
	    				out << abs(p.coefficient(i)) << "x^" << i << " ";
	    			}
    				break;

    		}
    		if(p.previous_term(i) != UINT_MAX)
    		{
    			i = p.previous_term(i);
    		} else
    		{
    			break;
    		}
    	}
    	if(p.is_zero())
    	{
    		out << 0;
    	}
    	else if(p.coefficient(0) != 0.0){
    		if(p.degree() == 0)
    		{
    			out << p.coefficient(0);
    			return out;
    		}
			(p.coefficient(0) >= 0) ? (out << "+ ") : (out << "- ");
			out << abs(p.coefficient(0));
    	}		
    	return out;
    };
}