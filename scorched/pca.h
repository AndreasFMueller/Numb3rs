/*
 * pca.h -- principal components analysis class
 *
 * (c) 2013 Prof Dr Andreas Mueller, Hochschule Rapperswil
 */
#ifndef _pca_h
#define _pca_h

#include "point.h"
#include "pointcloud.h"

class pca {
	double	_l1;
	double	_l2;
	point_t	_v1;
	point_t	_v2;
public:
	const double&	l1() const { return _l1; }
	const double&	l2() const { return _l2; }
	const point_t	v1() const { return _v1; }
	const point_t	v2() const { return _v2; }
	pca(const pointcloud_t& data);
	point_t	operator()(const double& t) const { return t * _v1; }
};

std::ostream&	operator<<(std::ostream& out, const pca& p);

#endif /* _pca_h */
