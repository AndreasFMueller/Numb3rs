/*
 * lr.h -- linear regression
 *
 * (c) 2013 Prof Dr Andreas Mueller, Hochschule Rapperswil
 */
#ifndef _lr_h
#define _lr_h

#include "point.h"
#include "pointcloud.h"

class lr {
	double	_a, _b;
public:
	double	a() const { return _a; }
	double	b() const { return _b; }
	lr(const pointcloud_t& data);
	point_t	operator()(const double& t) const {
		return point_t(t, _a * t + _b);
	}
};

std::ostream&	operator<<(std::ostream& out, const lr& l);

#endif /* _lr_h */
