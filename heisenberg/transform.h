/*
 * transform.h -- perform fourier transform of a function
 *
 * (c) 2014 Prof Dr Andreas Mueller, Hochschule Rappperswil
 */
#ifndef _transform_h
#define _transform_h

#include "sample.h"
#include <fftw3.h>

namespace heisenberg {

class transform {
	int	size(int n) const;
	double	abs(const fftw_complex& x) const;
public:
	vector	operator()(const vector& function) const;
};

} // namespace heisenberg

#endif /* _transform_h */
