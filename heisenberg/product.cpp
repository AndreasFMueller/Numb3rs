/*
 * product.cpp -- simulation of product property of function and fourier
 *                transform
 *
 * (c) 2014 Prof Dr Andreas Mueller, Hochschule Rapperswil
 */
#include <cstdlib>
#include <getopt.h>
#include "function.h"
#include "display.h"
#include "sample.h"
#include "transform.h"

namespace heisenberg {

int	main(int argc, char *argv[]) {
	functions	ff;
	function	*f = NULL;
	int	c;
	int	n = 101;
	double	sigma0 = 0.01165;
	bool	withvariance = false;
	while (EOF != (c = getopt(argc, argv, "f:s:n:v")))
		switch (c) {
		case 'f':
			f = ff.get(optarg, 1);
			break;
		case 's':
			sigma0 = atof(optarg);
			break;
		case 'n':
			n = atoi(optarg);
			break;
		case 'v':
			withvariance = true;
			break;
		}

	if (NULL == f) {
		std::cout << "no function defined" << std::endl;
		return EXIT_FAILURE;
	}

	// make it odd
	n -= n % 2;
	int	n2 = n / 2;

	for (int i = 0; i <= n; i++) {
		double	sigma = sigma0 * exp(3. * (i - n2) / n2);
		char	filename[1024];
		snprintf(filename, sizeof(filename), "prod/i%04d.mp", i);
		display	out(filename);

		sample	s(sigma, 30000);
		vector	x = s(*f);
		transform	F;
		vector	t = F(x);
		
		out.show_function(x, 200, withvariance);
		out.show_spectrum(t, 200, withvariance);
	}

	return EXIT_SUCCESS;
}

} // namespace heisenberg

int	main(int argc, char *argv[]) {
	try {
		return heisenberg::main(argc, argv);
	} catch (const std::exception& x) {
		std::cerr << "failure: " << x.what() << std::endl;
		return EXIT_FAILURE;
	}
}
