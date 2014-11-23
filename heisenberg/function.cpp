/*
 * function.cpp -- support functions for the function classes
 *
 * (c) 2014 Prof Dr Andreas Mueller, Hochschule Rapperswil
 */
#include "function.h"
#include <stdexcept>
#include <iostream>

namespace heisenberg {

double	function::operator()(const double x) const {
std::cerr << "base" << std::endl;
	return 0;
}

gauss::gauss(double sigma) : _mu(0), _sigma(sigma) {
}

double	gauss::operator()(const double x) const {
	double	v = exp(-sqr(x - _mu)/(2 * sqr(_sigma))) / (_sigma * sqrt(2 * M_PI));
	return v;
}

box::box(double a) : _a(a), _v(1 / (2 + _a)) {
}

double	box::operator()(const double x) const {
	return (fabs(x) < _a) ? _v : 0;
}

triangle::triangle(double a) : _a(a), _m(1 / a) {
}

double	triangle::operator()(const double x) const {
	if (fabs(x) > _a) { return 0; }
	return _m * (1 - fabs(x) / _a);
}

parabola::parabola(double r) : _r(r), _m(3 / (2 * r)) {
}

double	parabola:: operator()(const double x) const {
	if (fabs(x) > _r) { return 0; }
	return _m * (1 - sqr(x / _r));
}

cosine::cosine(double r) : _r(r), _m(1 / (2 * r)) {
}

double	cosine::operator()(const double x) const {
	if (fabs(x) > _r) { return 0; }
	return _m * cos(M_PI_2 * x / _r);
}

circle::circle(double r) : _r(r), _m(2 / (M_PI * r)) {
}

double	circle::operator()(const double x) const {
	double	xa = fabs(x);
	if (xa >= _r) {
		return 0;
	}
	xa = xa / _r;
	return _m * sqrt(1 - xa * xa);
}

spike::spike(double r) : _r(r), _m(1 / r) {
}

double	spike::operator()(const double x) const {
	double	xa = fabs(x);
	if (xa >= _r) {
		return 0;
	}
	xa = xa / _r;
	return _m * (1 - xa) * (1 - xa);
}

invcircle::invcircle(double r) : _r(r), _m(2 / ((4 - M_PI) * r)) {
}

double	invcircle::operator()(const double x) const {
	double	xa = fabs(x);
	if (xa >= _r) {
		return 0;
	}
	xa = 1 - xa / _r;
	return _m * (1 - sqrt(1 - xa * xa));
}

function	*functions::get(const std::string& name, double variance) {
	if (name == "gauss") {
		return new gauss(sqrt(variance));
	}
	if (name == "box") {
		return new box(sqrt(3 * variance));
	}
	if (name == "triangle") {
		return new triangle(sqrt(6 * variance));
	}
	if (name == "parabola") {
		return new parabola(sqrt(5 * variance / 2));
	}
	if (name == "cosine") {
		return new cosine(sqrt(M_PI * variance / (M_PI * M_PI - 8)));
	}
	if (name == "circle") {
		return new circle(sqrt(4 * variance));
	}
	if (name == "spike") {
		return new spike(sqrt(15 * variance));
	}
	if (name == "invcircle") {
		return new invcircle(sqrt(variance * 4 * (4 - M_PI)
					/ (16 - 5 * M_PI)));
	}
	throw std::runtime_error("unknown function");
}

} // namespace heisenberg
