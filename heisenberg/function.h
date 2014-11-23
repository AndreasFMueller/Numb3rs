/*
 * function.h -- function classes for heisenberg animation
 *
 * (c) 2014 Prof Dr Andreas Mueller, Hochschule Rapperswil
 */
#ifndef _function_h
#define _function_h

#include <math.h>
#include <string>

namespace heisenberg {

class function {
public:
	function() { }
	virtual ~function() { }
	virtual double	operator()(const double x) const;
};

class gauss : public function {
	double	_mu;
	double	_sigma;
	double	sqr(const double y) const { return y * y; }
public:
	gauss(double mu, double sigma) : _mu(mu), _sigma(sigma) { }
	gauss(double sigma);
	virtual double	operator()(const double x) const;
};

class box : public function {
	double	_a;
	double	_v;
public:
	box(double a, double v) : _a(fabs(a)), _v(v) { }
	box(double a);
	virtual double	operator()(const double x) const;
};

class triangle : public function {
	double	_a;
	double	_m;
public:
	triangle(double a, double m) : _a(fabs(a)), _m(m) { }
	triangle(double a);
	virtual double	operator()(const double x) const;
};

class parabola : public function {
	double	_r;
	double	_m;
	double	sqr(const double y) const { return y * y; }
public:
	parabola(double r, double m) : _r(fabs(r)), _m(m) { }
	parabola(double r);
	virtual double	operator()(const double x) const;
};

class cosine : public function {
	double	_r;
	double	_m;
public:
	cosine(double r, double m) : _r(fabs(r)), _m(m) { }
	cosine(double r);
	virtual double	operator()(const double x) const;
};

class circle : public function {
	double	_r;
	double	_m;
public:
	circle(double r, double m) : _r(fabs(r)), _m(m) { }
	circle(double r);
	virtual double	operator()(const double x) const;
};

class spike : public function {
	double	_r;
	double	_m;
public:
	spike(double r, double m) : _r(fabs(r)), _m(m) { }
	spike(double r);
	virtual double	operator()(const double x) const;
};

class invcircle : public function {
	double	_r;
	double	_m;
public:
	invcircle(double r, double m) : _r(fabs(r)), _m(m) { }
	invcircle(double r);
	virtual double	operator()(const double x) const;
};

class functions {
public:
	function	*get(const std::string& name, double variance);
};

class homotopy : public function {
	const function&	_f1;
	const function& _f2;
	double	_t;
public:
	homotopy(const function& f1, const function& f2, double t)
		: _f1(f1), _f2(f2), _t(t) { }
	virtual double	operator()(const double x) const {
		return (1 - _t) * _f1(x) + _t * _f2(x);
	}
};

} // namespace heisenberg

#endif /* _function_h */
