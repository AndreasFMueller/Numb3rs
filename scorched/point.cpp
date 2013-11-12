/*
 * point.cpp -- point stuff
 *
 * (c) 2013 Prof Dr Andreas Mueller, Hochschule Rapperswil
 */
#include "point.h"

point_t	operator-(const point_t& v) {
	return std::make_pair(-v.first, -v.second);
}

point_t	operator+(const point_t& a, const point_t& b) {
	return std::make_pair(a.first + b.first, a.second + b.second);
}

point_t	operator-(const point_t& a, const point_t& b) {
	return std::make_pair(a.first - b.first, a.second - b.second);
}

point_t	operator*(const double& lambda, const point_t& v) {
	return std::make_pair(lambda * v.first, lambda * v.second);
}

point_t	operator*(const point_t& v, const double& lambda) {
	return std::make_pair(lambda * v.first, lambda * v.second);
}

double	operator*(const point_t& a, const point_t& b) {
	return a.first * b.first + a.second * b.second;
}

static inline double	sqr(double x) {
	return x * x;
}

double	norm(const point_t& v) {
	return sqrt(sqr(v.first) + sqr(v.second));
}

point_t	operator/(const point_t& v, const double& lambda) {
	return std::make_pair(v.first / lambda, v.second / lambda);
}

std::ostream&	operator<<(std::ostream& out, const point_t& p) {
	return out << "(" << p.first << "," << p.second << ")";
}

