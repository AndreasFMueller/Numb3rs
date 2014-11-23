/*
 * deform.cpp -- deform functions from gauss to others to see how they deform
 *
 * (c) 2014 Prof Dr Andreas Mueller, Hochschule Rapperswil
 */
#include <stdexcept>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <getopt.h>
#include "function.h"
#include "display.h"
#include "sample.h"
#include "transform.h"

namespace heisenberg {

int	filenumber = 0;
double	sigma0 = 0.0002;

void	showfile(const homotopy& h, bool withvariance) {
	char	filename[1024];
	snprintf(filename, sizeof(filename), "def/i%04d.mp", filenumber++);
	display	out(filename);
	sample	s(sigma0, 30000);
	vector	x = s(h);
	transform	F;
	vector	t = F(x);
	out.show_function(x, 600, false);
	out.show_spectrum(t, 600, withvariance);
}

void	showdeformation(const function& f1, const function& f2, int n,
		bool withvariance) {
	for (int i = 0; i <= n; i++) {
		double	l = (double)i / (double)n;
		homotopy	h(f1, f2, l);
		showfile(h, withvariance);
	}
}

int	main(int argc, char  *argv[]) {
	bool	withvariance = false;
	filenumber = 0;
	int	c;
	while (EOF != (c = getopt(argc, argv, "v")))
		switch (c) {
		case 'v':
			withvariance = true;
			break;
		}

	int	n = 100;
	functions	ff;
	function	*fgauss = ff.get("gauss", sigma0);
	function	*fbox = ff.get("box", sigma0);
	function	*ftriangle = ff.get("triangle", sigma0);
	function	*fparabola = ff.get("parabola", sigma0);
	function	*fcosine = ff.get("cosine", sigma0);
	function	*fcircle = ff.get("circle", sigma0);
	function	*fspike = ff.get("spike", sigma0);
	function	*finvcircle = ff.get("invcircle", sigma0);

	showdeformation(*fgauss, *fbox, n, withvariance);
	showdeformation(*fbox, *fgauss, n, withvariance);
	showdeformation(*fgauss, *ftriangle, n, withvariance);
	showdeformation(*ftriangle, *fgauss, n, withvariance);
	showdeformation(*fgauss, *fparabola, n, withvariance);
	showdeformation(*fparabola, *fgauss, n, withvariance);
	showdeformation(*fgauss, *fcosine, n, withvariance);
	showdeformation(*fcosine, *fgauss, n, withvariance);
	showdeformation(*fgauss, *fcircle, n, withvariance);
	showdeformation(*fcircle, *fgauss, n, withvariance);
	showdeformation(*fgauss, *fspike, n, withvariance);
	showdeformation(*fspike, *fgauss, n, withvariance);
	showdeformation(*fgauss, *finvcircle, n, withvariance);
	showdeformation(*finvcircle, *fgauss, n, withvariance);

	return EXIT_SUCCESS;
}

} // namespace heisenberg

int	main(int argc, char *argv[]) {
	try {
		return heisenberg::main(argc, argv);
	} catch (const std::exception& x) {
		std::cerr << "exception: " << x.what() << std::endl;
	}
}
