/*
 * lr.cpp -- linear regression
 *
 * (c) 2013 Prof Dr Andreas Mueller, Hochschule Rapperswil
 */
#include "lr.h"

std::ostream&	operator<<(std::ostream& out, const lr& l) {
	out << "a = " << l.a() << ", b = " << l.b() << std::endl;
	return out;
}

lr::lr(const pointcloud_t& data) {
	double	X = std::for_each(data.begin(), data.end(), accumulator(x));
	double	Y = std::for_each(data.begin(), data.end(), accumulator(y));
	double	X2 = std::for_each(data.begin(), data.end(), accumulator(x2));
	double	XY = std::for_each(data.begin(), data.end(), accumulator(xy));
	int	n = data.size();
	_a = (n * XY - X * Y) / (n * X2 - X * X);
	_b = (Y - _a * X) / n;
}
