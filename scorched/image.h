/*
 * image.h -- image 
 * 
 * (c) 2013 Prof Dr Andreas Mueller
 */
#ifndef _image_h
#define _image_h

#include "pointcloud.h"
#include "lr.h"
#include "pca.h"

class image {
	const pointcloud_t&	_data;
	const lr&	_lr;
	const pca&	_pca;
public:
	const pointcloud_t&	data() const { return _data; }
	const pca&	pca() const { return _pca; }
	const lr&	lr() const { return _lr; }
	image(const pointcloud_t& data, const class lr& l, const class pca& p)
		: _data(data), _lr(l), _pca(p) { }
};

std::ostream&	operator<<(std::ostream& out, const image& im);

#endif /* _image_h */
