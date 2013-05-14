/*
 * draw.cpp -- draw an elliptic curve
 */
#include <ec.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>

class	rectangle {
public:
	double	x, y;
	double	width, height;
	rectangle() { }
	bool	contains(const Point& p) {
		double	X = p.x/p.z;
		double	Y = p.y/p.z;
		if ((X < x) || ((x + width) < X)) {
			return false;
		}
		if ((Y < y) || ((y + height) < Y)) {
			return false;
		}
		return true;
	}
};

void	preamble(std::ostream& out) {
	out << "verbatimtex" << std::endl;
	out << "%&latex" << std::endl;
	out << "\\documentclass{article}" << std::endl;
	out << "\\usepackage{times}" << std::endl;
	out << "\\usepackage{amsmath}" << std::endl;
	out << "\\usepackage{amssymb}" << std::endl;
	out << "\\usepackage{amsfonts}" << std::endl;
	out << "\\usepackage{txfonts}" << std::endl;
	out << "\\begin{document}" << std::endl;
	out << "etex;" << std::endl;
}

void	postamble(std::ostream& out) {
	out << "end" << std::endl;
}

void	drawcurve(std::ostream& out, const EllipticCurve& curve) {
	double	step = 0.025;
	out << "pickup pencircle scaled 2pt;" << std::endl;

	out << "draw " << Point(-1,0) << "{dir 90}";
	for (double x = -1 + step; x < 0; x += step) {
		out << ".." << curve.point(x);
	}
	out << ".." << Point(0,0);
	for (double x = -step; x > -1; x -= step) {
		out << ".." << curve.invert(curve.point(x));
	}
	out << ".." << Point(-1,0) << "{dir 90} withcolor(1,0,0);" << std::endl;

	out << "draw " << curve.point(2);
	for (double x = 2 - step; x > 1; x -= step) {
		out << ".." << curve.point(x);
	}
	out << ".." << Point(1,0);
	for (double x = 1 + step; x < 2; x += step) {
		out << ".." << curve.invert(curve.point(x));
	}
	out << " withcolor (1,0,0);" << std::endl;
	out << "clip currentpicture to " << Point(-1.1,-1.1)
		<< "--" << Point(2.1,-1.1)
		<< "--" << Point(2.1,1.1)
		<< "--" << Point(-1.1,1.1) << "--cycle;" << std::endl;
}

void	drawaxes(std::ostream& out) {
	out << "pickup pencircle scaled 1pt;" << std::endl;
	out << "drawarrow " << Point(-1.1,0) << "--" << Point(2.1,0)
		<< ";" << std::endl;
	out << "drawarrow " << Point(0,-1.1) << "--" << Point(0,1.1)
		<< ";" << std::endl;
}

void	drawoperation(std::ostream& out, const EllipticCurve& curve) {
	Point	a = curve.point(-0.95);
	Point	b = curve.point(-0.15);
	Point	c = curve.product(a,b);
	Point	d = curve.invert(c);
	out << "z0 = " << a << ";" << std::endl;
	out << "z1 = " << b << ";" << std::endl;
	out << "z2 = " << c << ";" << std::endl;
	out << "z3 = " << d << ";" << std::endl;
	out << "pickup pencircle scaled 1pt;" << std::endl;
	out << "draw (-0.05)[z0,z2]--(1.1)[z0,z2] withcolor (0.7,0.7,1);" << std::endl;
	out << "draw (-0.2)[z2,z3]--(1.2)[z2,z3] withcolor (0.7,0.7,1);" << std::endl;
	out << "pickup pencircle scaled 5pt;" << std::endl;
	out << "draw z0 withcolor (0,0,1);" << std::endl;
	out << "label.ulft(btex $A$ etex, z0) withcolor(0,0,1);" << std::endl;
	out << "label.urt(btex $B$ etex, z1) withcolor(0,0,1);" << std::endl;
	out << "label.ulft(btex $C$ etex, z2) withcolor(0,0,1);" << std::endl;
	out << "label.rt(btex $D = A \\star B$ etex, z3) withcolor(0,0,1);" << std::endl;
	out << "draw z1 withcolor (0,0,1);" << std::endl;
	out << "draw z2 withcolor (0,0,1);" << std::endl;
	out << "draw z3 withcolor (0,0,1);" << std::endl;
}

void	drawsquare(std::ostream& out, const EllipticCurve& curve) {
	Point	a = curve.point(-0.3);
	Point	b = curve.sqr(a);
	Point	c = curve.invert(b);
	out << "z0 = " << a << ";" << std::endl;
	out << "z1 = " << b << ";" << std::endl;
	out << "z2 = " << c << ";" << std::endl;
	out << "pickup pencircle scaled 1pt;" << std::endl;
	out << "draw (-0.4)[z0,z1]--(1.4)[z0,z1] withcolor (0.7,0.7,1);" << std::endl;
	out << " draw (-0.4)[z1,z2]--(1.4)[z1,z2] withcolor (0.7,0.7,1);" << std::endl;
	out << "pickup pencircle scaled 5pt;" << std::endl;
	out << "draw z0 withcolor (0,0,1);" << std::endl;
	out << "draw z1 withcolor (0,0,1);" << std::endl;
	out << "draw z2 withcolor (0,0,1);" << std::endl;
	out << "label.urt(btex $A$ etex, z0) withcolor(0,0,1);" << std::endl;
	out << "label.llft(btex $B$ etex, z1) withcolor(0,0,1);" << std::endl;
	out << "label.rt(btex $C=A\\star A$ etex, z2) withcolor(0,0,1);" << std::endl;
}

static double	lag = 0;
static double	mindiam = 3.;
static double	maxdiam = 3.;

void	drawpowers(std::ostream& out, const EllipticCurve& curve, int n) {
	out << "pickup pencircle scaled 5pt;" << std::endl;
	Point	a = curve.point(-0.22);
	out << "draw " << a << " withcolor(0,0,1);" << std::endl;
	Point	b = curve.invert(curve.sqr(a));
	int	i = 0;
	rectangle	r;
	r.x = -1.1;
	r.y = -1.1;
	r.width = 3.2;
	r.height = 2.2;
	double	delta = maxdiam - mindiam;
	if (lag > 0) {
		delta /= lag;
	} else {
		delta = 0;
	}
	while (i++ < n) {
		out << "pickup pencircle scaled ";
		if ((n - i) > lag) {
			out << mindiam;
		} else {
			out << maxdiam - delta * (n - i);
		}
		out << "pt;" << std::endl;
		if (r.contains(b)) {
			out << "draw " << b << " withcolor(0,0,1);"
				<< std::endl;
		}
		b = curve.invert(curve.product(a, b));
	}
}

void	do_curve() {
	EllipticCurve	curve(-1, 0);
	scale = 100;
	preamble(std::cout);
	std::cout << "beginfig(1)" << std::endl;
	drawcurve(std::cout, curve);
	drawaxes(std::cout);
	std::cout << "endfig;" << std::endl;
	postamble(std::cout);
}

void	do_operation() {
	EllipticCurve	curve(-1, 0);
	scale = 100;
	preamble(std::cout);
	std::cout << "beginfig(1)" << std::endl;
	drawcurve(std::cout, curve);
	drawoperation(std::cout, curve);
	drawaxes(std::cout);
	std::cout << "endfig;" << std::endl;
	postamble(std::cout);
}

void	do_square() {
	EllipticCurve	curve(-1, 0);
	scale = 100;

	preamble(std::cout);
	std::cout << "beginfig(1)" << std::endl;
	drawcurve(std::cout, curve);
	drawsquare(std::cout, curve);
	drawaxes(std::cout);
	std::cout << "endfig;" << std::endl;
	postamble(std::cout);
}

void	do_powers(int n) {
	EllipticCurve	curve(-1, 0);
	scale = 100;
	preamble(std::cout);
	std::cout << "beginfig(1)" << std::endl;
	drawcurve(std::cout, curve);
	drawpowers(std::cout, curve, n);
	drawaxes(std::cout);
	std::cout << "endfig;" << std::endl;
	postamble(std::cout);
}

void	do_videoimage(int i, const EllipticCurve& curve, std::ostream& out) {
	out << "beginfig(" << i + 1 << ")" << std::endl;
	drawcurve(out, curve);
	drawpowers(out, curve, i);
	drawaxes(out);
	out << "endfig;" << std::endl;
}

void	do_video(int n) {
	EllipticCurve	curve(-1, 0);
	scale = 100;
	preamble(std::cout);
	for (int i = 0; i < n; i++) {
		do_videoimage(i, curve, std::cout);
	}
	postamble(std::cout);
}

void	do_ausschnitt(int n) {
	EllipticCurve	curve(-1, 0);
	scale = 30000;
	preamble(std::cout);
	double	xmin = -0.31;
	double	xmax = -0.30;
	std::cout << "beginfig(1)" << std::endl;
	Point	ul = curve.point(xmin);
	Point	lr = curve.point(xmax);
	Point	ur(lr.x, ul.y);
	Point	ll(ul.x, lr.y);
	xoffset = ul.x / ul.z;
	yoffset = lr.y / lr.z;
	rectangle	r;
	r.x = ul.x;
	r.y = lr.y;
	r.width = lr.x - ul.x;
	r.height = ul.y - lr.y;
fprintf(stderr, "r= %f %f %f %f\n", r.x, r.y, r.width, r.height);
	std::cout << "pickup pencircle scaled 1pt;" << std::endl;
	std::cout << "draw " << ll << "--" << lr << "--" << ur
		<< "--" << ul << "--cycle;" << std::endl;

	std::cout << "pickup pencircle scaled 2pt;" << std::endl;
	std::cout << "draw " << ul;
	for (int i = 1; i <= 10; i++) {
		Point	p = curve.point(xmin + i * (xmax - xmin) / 10);
		std::cout << "--" << p;
	}
	std::cout << " withcolor(1,0,0);" << std::endl;
	
	Point	a = curve.point(-0.22);
	//std::cout << "draw " << a << " withcolor(0,0,1);" << std::endl;
	Point	b = curve.invert(curve.sqr(a));
	int	k = 0;
	std::cout << "pickup pencircle scaled 5pt;";
	while (k++ < n) {
		if (r.contains(b)) {
			if (k > 2000) {
				std::cout << "draw " << b << " withcolor(0,0,1);"
					<< std::endl;
				std::cout << "label.urt(btex $" << k << "$ etex," << b << ");" << std::endl;
			}
		}
		b = curve.invert(curve.product(a, b));
	}
	std::cout << "endfig;" << std::endl;
	postamble(std::cout);
}

int	main(int argc, char *argv[]) {
	if (std::string(argv[1]) == std::string("curve")) {
		do_curve();
	}
	if (std::string(argv[1]) == std::string("operation")) {
		do_operation();
	}
	if (std::string(argv[1]) == std::string("square")) {
		do_square();
	}
	if (std::string(argv[1]) == std::string("powers")) {
		do_powers(150);
	}
	if (std::string(argv[1]) == std::string("video")) {
		do_video(1000);
	}
	if (std::string(argv[1]) == std::string("ausschnitt")) {
		do_ausschnitt(10000);
	}
}
