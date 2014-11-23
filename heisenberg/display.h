/*
 * display.h -- display function and its fourier transform in metapost
 *
 * (c) 2014 Prof Dr Andreas Mueller, Hochschule Rapperswil
 */
#ifndef _display_h
#define _display_h

#include "sample.h"
#include <iostream>
#include <fstream>

namespace heisenberg {

class display {
	double	width, height;
	void	setup();
	std::ofstream	out;
private:	// don't copy
	display(const display& other);
	display&	operator=(const display& other);
public:
	display(char *filename);
	display(const std::string& filename);
	~display();
private:
	void	show(const vector& v, int window, double yoffset,
		bool withvariance = true);
	std::string	coord(double x) const;
public:
	void	show_function(const vector& f, int window,
			bool withvariance = true);
	void	show_spectrum(const vector& s, int window,
			bool withvariance = true);
};

} // namespace heisenberg

#endif /* _display_h */
