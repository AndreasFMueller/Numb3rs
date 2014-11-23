/*
 * sample.cpp -- sample a function into a vector
 *
 * (c) 2014 Prof Dr Andreas Mueller, Hochschule Rapperswil
 */
#include "sample.h"
#include <stdexcept>
#include <iostream>

namespace heisenberg {

vector::vector(int n) : _n(n) {
	s = new double[2 * _n + 1];
}

vector::~vector() {
	delete[] s;
}

vector::vector(const vector& other) {
	_n = other._n;
	s = new double[2 * _n + 1];
	for (int i = 0; i <= 2 * _n; i++) {
		s[i] = other.s[i];
	}
}

vector&	vector::operator=(const vector& other) {
	delete[] s;
	_n = other._n;
	s = new double[2 * _n + 1];
	for (int i = 0; i <= 2 * _n; i++) {
		s[i] = other.s[i];
	}
	return *this;
}

double&	vector::operator[](int i) {
	if ((i < -_n) || (i > _n)) {
		throw std::range_error("out of range");
	}
	return s[i + _n];
}

const double&	vector::operator[](int i) const {
	if ((i < -_n) || (i > _n)) {
		throw std::range_error("out of range");
	}
	return s[i + _n];
}

static double	sqr(double y) {
	return y * y;
}

double	vector::variance(int window) const {
	if (window < 0) {
		window = _n;
	}
	double	x2sum = 0;
	double	sum = 0;
	for (int i = -window; i <= window; i++) {
		double	v = this->operator[](i);
		sum += fabs(v);
		x2sum += fabs(v) * sqr((double)i);
	}
	return x2sum / sum;
}

vector	sample::operator()(const function& f) const {
std::cerr << "sampling" << std::endl;
	vector	result(_n);
	for (int i = -_n; i <= _n; i++) {
		double	x = _h * i;
		result[i] = f(x);
//std::cerr << "i = " << i << ", x = " << x << ", f(x) = " << result[i] << std::endl;
	}
	return result;
}

} // namespace heisenberg
