/*
 * image.cpp
 *
 * (c) 2013 Prof Dr Andreas Mueller, Hochschule Rapperswil
 */
#include "image.h"

std::ostream&	operator<<(std::ostream& out, const image& im) {
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
	out << "beginfig(1);" << std::endl;

	// coordinate system
	out << "pickup pencircle scaled 1pt;" << std::endl;
	out << "draw (-140,0)--(140,0);" << std::endl;
	out << "draw (0,-100)--(0,100);" << std::endl;

	// define all points
	out << "z0 = (0,0);" << std::endl;
	int	counter = 1;
	for (pointcloud_t::const_iterator i = im.data().begin();
		i != im.data().end(); i++) {
		out << "z" << counter << " = " << (20 * (*i)) << ";"
			<< std::endl;
		counter++;
	}

	// display the principal directions
	out << "pickup pencircle scaled 1pt;" << std::endl;
	out << "draw "
		<< (140. * im.pca().v1()) << "--" << (-140. * im.pca().v1())
		<< " withcolor(1.0,0.0,0.0);" << std::endl;
	out << "draw "
		<< (140. * im.pca().v2()) << "--" << (-140. * im.pca().v2())
		<< " withcolor(1.0,0.0,0.0);" << std::endl;

	// display the distances to the linear regression line
	out << "pickup pencircle scaled 0.1pt;" << std::endl;
	counter = 1;
	for (pointcloud_t::const_iterator i = im.data().begin();
		i != im.data().end(); i++, counter++) {
		point_t	p = im.lr()(x(i));
		out << "draw z" << counter << "--" << (20 * p)
			<< " withcolor (0.0,0.0,1.0);" << std::endl;
	}

	// display the linear regression lines
	out << "pickup pencircle scaled 1pt;" << std::endl;
	out << "draw " << im.lr()(-140) << "--" << im.lr()(140) 
		<< " withcolor(0.0,0.0,1.0);" << std::endl;

	// clip 
	out << "clip currentpicture to "
		<< "(-140,-100)--(140,-100)--(140,100)--(-140,100)--cycle;"
		<< std::endl;

	// draw the points
	out << "pickup pencircle scaled 3pt;" << std::endl;
	counter = 1;
	for (pointcloud_t::const_iterator i = im.data().begin();
		i != im.data().end(); i++) {
		out << "draw z" << counter << ";" << std::endl;
		counter++;
	}
	
	out << "endfig;" << std::endl;
	out << "end" << std::endl;
	return out;
}
