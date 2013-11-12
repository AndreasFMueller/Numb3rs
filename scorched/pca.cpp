/*
 * pca.cpp -- principal components analysis class
 *
 * (c) 2013 Prof Dr Andreas Mueller, Hochschule Rapperswil
 */
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cmath>
#include "pca.h"

std::ostream&	operator<<(std::ostream& out, const pca& p) {
	out << "l1 = " << p.l1() << ", v1 = " << p.v1() << std::endl;
	out << "l2 = " << p.l2() << ", v2 = " << p.v2() << std::endl;
	return out;
}

static inline double	sqr(double x) { return x * x; }

pca::pca(const pointcloud_t& data) {
	double	X2 = std::for_each(data.begin(), data.end(), accumulator(x2));
	double	Y2 = std::for_each(data.begin(), data.end(), accumulator(y2));
	double	XY = std::for_each(data.begin(), data.end(), accumulator(xy));
	double	delta = X2 - Y2;
	double	trace = X2 + Y2;
	double	d = sqrt(sqr(delta) + 4 * sqr(XY));
	_l1 = 0.5 * (trace + d);
	_l2 = 0.5 * (trace - d);
	_v1 = point_t(XY, 0.5 * (d - delta));
	_v1 = _v1 / norm(_v1);
	_v2 = point_t(XY, -0.5 * (delta + d));
	_v2 = _v2 / norm(_v2);
}

