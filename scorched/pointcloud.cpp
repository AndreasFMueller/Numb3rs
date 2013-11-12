/*
 * pointcloud.h
 *
 * (c) 2013 Prof Dr Andreas Mueller, Hochschule Rapperswil
 */
#include "pointcloud.h"

class pointcloudreverser {
	pointcloud_t	result;
public:
	void	operator()(const point_t& v) {
		result.push_back(-v);
	}
	operator pointcloud_t() { return result; }
};

pointcloud_t	operator-(const pointcloud_t& data) {
	return std::for_each(data.begin(), data.end(), pointcloudreverser());
}

class pointcloudtranslator {
	const point_t&	_v;
	pointcloud_t	result;
public:
	pointcloudtranslator(const point_t& v) : _v(v) { }
	void	operator()(const point_t& u) {
		result.push_back(u + _v);
	}
	operator pointcloud_t () { return result; }
};

pointcloud_t	operator+(const pointcloud_t& data, const point_t& v) {
	return std::for_each(data.begin(), data.end(), pointcloudtranslator(v));
}

pointcloud_t	operator+(const point_t& v, const pointcloud_t& data) {
	return data + v;
}

pointcloud_t	operator-(const pointcloud_t& data, const point_t& v) {
	return -v + data;
}

pointcloud_t	operator-(const point_t& v, const pointcloud_t& data) {
	return -data + v;
}

class pointcloudrotator {
	const rotation&	_rot;
	pointcloud_t	result;
public:
	pointcloudrotator(const rotation& rot) : _rot(rot) { }
	void	operator()(const point_t& p) {
		result.push_back(_rot(p));
	}
	operator pointcloud_t () { return result; }
};

pointcloud_t	operator*(const rotation& rot, const pointcloud_t v) {
	return std::for_each(v.begin(), v.end(), pointcloudrotator(rot));
}

point_t	center(const pointcloud_t& data) {
	double	X = std::for_each(data.begin(), data.end(), accumulator(x));
	double	Y = std::for_each(data.begin(), data.end(), accumulator(y));
	int n	= data.size();
	return point_t(X / n, Y / n);;
}

