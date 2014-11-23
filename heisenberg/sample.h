/*
 * sample.h -- sample a function
 *
 * (c) 2014 Prof Dr Andreas Mueller, Hochschule Rapperswil
 */
#ifndef _sample_h
#define _sample_h

#include "function.h"

namespace heisenberg {

class vector {
	double	*s;
	int	_n;
public:
	int	n() const { return _n; }
	int	size() const { return 2 * _n + 1; }
	vector(int n);
	~vector();
	vector(const vector& other);
	vector&	operator=(const vector& other);
	double&	operator[](int i);
	const double&	operator[](int i) const;
	double	variance(int window = 0) const;
};

class sample {
	double	_h;
	int	_n;
public:
	sample(double h, int n) : _h(h), _n(n) { }
	vector	operator()(const function& f) const;
};

} // namespace heisenberg

#endif /* _sample_h */
