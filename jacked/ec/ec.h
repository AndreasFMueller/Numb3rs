/*
 * ec.h -- elliptic curve utilities
 *
 * (c) 2013 Prof Dr Andreas Mueller, Hochschule Rapperswil
 */
#ifndef _ec_h
#define _ec_h

#include <iostream>

extern double	scale;
extern double	xoffset;
extern double	yoffset;

/*
 * class representing points in the plane
 */
class Point {
public:
	void	normalize();
	double	x, y, z;
	Point(const double& _x, const double& _y, const double& _z)
		: x(_x), y(_y), z(_z) { }
	Point(const double& _x, const double& _y) : x(_x), y(_y), z(1) {
		normalize();
	}
	Point();
	double	rescale(double v) const;
};

std::ostream&	operator<<(std::ostream& out, const Point& p);


/*
 * structure encoding the elliptic curve
 *
 *    y^2z = x^3 + axz^2 + bz^3
 *
 */
class EllipticCurve {
	double	a, b;
public:
	EllipticCurve(const double& _a, const double& _b) : a(_a), b(_b) { }
	double	verify(const Point& u) const;
	Point	invert(const Point& u) const;
	Point	product(const Point& u, const Point& v) const;
	Point	sqr(const Point& u) const;
	Point	pow(const Point& u, int n) const;
	Point	point(double x) const;
};

#endif /* _ec_h */
