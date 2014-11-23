/*
 * transform.cpp -- fourier transform using fftw3
 *
 * (c) 2014 Prof Dr Andreas Mueller, Hochschule Rapperswil
 */
#include "transform.h"
#include <fftw3.h>
#include <iostream>

namespace heisenberg {

int	transform::size(int n) const {
	int	result = 1;
	do {
		result <<= 1;
	} while (!(result >= n));
std::cerr << "size: " << n << " -> " << result << std::endl;
	return result;
}

double	transform::abs(const fftw_complex& x) const {
	return hypot(x[0], x[1]);
}

vector	transform::operator()(const vector& f) const {
	// find the dimensions we need for the vector
	int	n = size(f.size());

	// allocate a vector for the fourier transform to operate on
	double	x[n];
	for (int i = 0; i < n; i++) {
		x[i] = 0;
	}

	// copy the data into that vector
	for (int i = 0; i <= f.n(); i++) {
		x[i] = sqrt(fabs(f[i]));
	}
	for (int i = -1; i >= -f.n(); i--) {
		x[n + i] = sqrt(fabs(f[i]));
	}
std::cerr << "transform initialized" << std::endl;
//for (int i = 0; i < n; i++) {
//	std::cerr << "x[" << i << "] = " << x[i] << std::endl;
//}
std::cerr << "size: " << (1 + n/2) << std::endl;

	// create an array for the transform result
	fftw_complex	*t = fftw_alloc_complex(1 + n/2);

	// perform the fourier transform
	fftw_plan	plan = fftw_plan_dft_r2c_1d(n, x, t,
				FFTW_ESTIMATE | FFTW_PRESERVE_INPUT);
	fftw_execute(plan);

	// copy the data into a result vector of the same size
	vector	result(f.n());
	result[0] = abs(t[0]);
	for (int i = 1; i < result.n(); i++) {
//std::cerr << t[i][0] << " + " << t[i][1] << " * I" << std::endl;
		double	v = abs(t[i]);
		result[i] = v;
		result[-i] = v;
	}
//for (int i = 0; i < n; i++) {
//	std::cerr << "v[" << i << "] = " << result[i] << std::endl;
//}

	// cleanup
	fftw_destroy_plan(plan);
	fftw_free(t);

	return result;
}

} // namespace heisenberg
