/*
 * pointcloud.h -- pointcloud stuff
 *
 * (c) 2013 Prof Dr Andreas Mueller, Hochschule Rapperswil
 */
#ifndef _pointcloud_h
#define _pointcloud_h

#include "point.h"
#include <cstdlib>
#include <vector>
#include <iostream>

typedef	std::vector<std::pair<double, double> >	pointcloud_t;
typedef pointcloud_t::const_iterator	point_iterator;

inline double	x(const point_iterator& i) { return x(*i); }
inline double	x2(const point_iterator& i) { return x2(*i); }
inline double	y(const point_iterator& i) { return y(*i); }
inline double	y2(const point_iterator& i) { return y2(*i); }
inline double	xy(const point_iterator& i) { return xy(*i); }

pointcloud_t	operator-(const pointcloud_t& data);
pointcloud_t	operator+(const pointcloud_t& data, const point_t& v);
pointcloud_t	operator+(const point_t& v, const pointcloud_t& data);
pointcloud_t	operator-(const pointcloud_t& data, const point_t& v);
pointcloud_t	operator-(const point_t& v, const pointcloud_t& data);
pointcloud_t	operator*(const rotation& rot, const pointcloud_t v);

class pointgenerator {
	double	_width;
	double	_height;
	double	random(double length) const {
		return length * (::random() / (double)0x7fffffff);
	}
public:
	double	width() const { return _width; }
	double	height() const { return _height; }
	pointgenerator(const double& width, const double& height)
		: _width(width), _height(height) { }
	point_t	point() const {
		double	x = random(_width);
		double	y = random(_height);
		return point_t(x, y);
	}
	point_t	operator()() const { return point(); }
	pointcloud_t	operator()(int n) const {
		pointcloud_t	result;
		std::generate_n(back_inserter(result), n, *this);
		return result;
	}
};

typedef double	(extractor)(const point_t&);

class accumulator {
	double	_sum;
	double	_n;
	extractor&	_f;
public:
	double	sum() const { return _sum; }
	double	n() const { return _n; }
	accumulator(extractor& f) : _sum(0), _n(0), _f(f) { }
	void	operator()(const point_t& p) {
		_sum += _f(p);
		_n++;
	}
	operator double	() { return sum(); }
};

point_t	center(const pointcloud_t& data);

#endif /* _pointcloud_h */
