/*
 * point.h -- point stuff
 *
 * (c) 2013 Prof Dr Andreas Mueller, Hochschule Rapperswil
 */
#ifndef _point_h
#define _point_h

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cmath>

typedef std::pair<double, double>	point_t;

inline double	x(const point_t& p) { return p.first; }
inline double	x2(const point_t& p) { return x(p) * x(p); }
inline double	y(const point_t& p) { return p.second; }
inline double	y2(const point_t& p) { return y(p) * y(p); }
inline double	xy(const point_t& p) { return x(p) * y(p); }

point_t	operator-(const point_t& v);
point_t	operator+(const point_t& a, const point_t& b);
point_t	operator-(const point_t& a, const point_t& b);
point_t	operator*(const double& lambda, const point_t& v);
point_t	operator*(const point_t& v, const double& lambda);
double	operator*(const point_t& a, const point_t& b);
double	norm(const point_t& v);
point_t	operator/(const point_t& v, const double& lambda);

std::ostream&	operator<<(std::ostream& out, const point_t& p);

class rotation {
	point_t	column1, column2;
public:
	rotation(const double& angle) {
		column1 = point_t(cos(angle), -sin(angle));
		column2 = point_t(sin(angle), cos(angle));
	}
	point_t	operator()(const point_t& v) const {
		return v.first * column1 + v.second * column2;
	}
	point_t	operator*(const point_t& v) const {
		return operator()(v);
	}
};

#endif /* _point_h */
