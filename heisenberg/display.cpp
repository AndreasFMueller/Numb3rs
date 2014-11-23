/*
 * display.cpp -- display a pair of vectors in Metapost
 *
 * (c) 2014 Prof Dr Andreas Mueller, Hochschule Rapperswil
 */
#include "display.h"

namespace heisenberg {

void	display::setup() {
	width = 320;
	height = 240;
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
	out << "beginfig(1)" << std::endl;
	out << "pickup pencircle scaled 1pt;" << std::endl;
	out << "drawarrow (-" << (width / 2) << ",0)--(";
	out << (width / 2) << ",0);" << std::endl;
	double	h = (height - 40) / 2;
	out << "drawarrow (-" << (width / 2) << "," << ((height - 40) / 2);
	out << ")--(";
	out << (width / 2) << "," << h << ");" << std::endl;
	out << "drawarrow (0," << (h - 5) << ")--(0,";
	out << (1.8 * h + 5) << ");" << std::endl;
	out << "drawarrow (0,-5)--(0," << (0.8 * h + 5) << ");" << std::endl;
	out << "label.ulft(btex $k$ etex, (" << (width / 2) << ",0));"
		<< std::endl;
	out << "label.ulft(btex $x$ etex, (" << (width / 2) << "," << h << "));"
		<< std::endl;
}

display::display(char *filename) : out(filename) {
	setup();
}

display::display(const std::string& filename) : out(filename.c_str()) {
	setup();
}

display::~display() {
	out << "endfig;" << std::endl;
	out << "end" << std::endl;
	out.close();
}

std::string	display::coord(double x) const {
	char	buffer[100];
	snprintf(buffer, sizeof(buffer), "%.2f", x);
	return std::string(buffer);
}

void	display::show(const vector& v, int window, double yoffset,
		bool withvariance) {
	double	w = (width - 20);
	double	h = (height - 40);
	double	xstep = w / (2 * window);
	double	yscale = 0.8 * h / (2 * v[0]);

	double	n = xstep * sqrt(v.variance(-1));
#if 0
	if (n < w/2) {
		n = xstep * sqrt(v.variance(window));
	}
#endif
	n = xstep * sqrt(v.variance(900));
std::cerr << "variance: n = " << n << std::endl;
	if ((withvariance) && (n < (w / 2))) {
		out << "pickup pencircle scaled 2.0;" << std::endl;
		out << "draw (" << coord(n) << ",";
		out << coord(yoffset - 5) << ")";
		out << "--";
		out << "(" << coord(n) << ",";
		out << coord(yoffset + 0.4 * h + 5) << ")";
		out << "withcolor(0.0,0.0,1.0);" << std::endl;
		out << "draw (" << coord(-n) << ",";
		out << coord(yoffset - 5) << ")";
		out << "--";
		out << "(" << coord(-n) << ",";
		out << coord(yoffset + 0.4 * h + 5) << ")";
		out << "withcolor(0.0,0.0,1.0);" << std::endl;
	}
	out << "pickup pencircle scaled 1.4pt;" << std::endl;
	out << "draw";
	out << "(" << coord(xstep * (-window)) << ",";
	out << coord(yscale * v[-window] + yoffset) << ")";
	for (int i = -window + 1; i <= window; i++) {
		out << "--(";
		out << coord(xstep * i);
		out << ",";
		out << coord(yscale * v[i] + yoffset);
		out << ")" << std::endl;
	}
	out << "withcolor(1,0,0)";
	out << ";" << std::endl;
}

void	display::show_function(const vector& f, int window, bool withvariance) {
	show(f, window, (height - 40) / 2, withvariance);
}

void	display::show_spectrum(const vector& s, int window, bool withvariance) {
	show(s, window, 0, withvariance);
}

} // namespace heisenberg
