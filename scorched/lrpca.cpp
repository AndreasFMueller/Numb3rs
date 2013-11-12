/*
 * lrpca.cpp -- programm to generate frames for a demo video comparing
 *              principal components analysis to linear regression
 *
 * (c) 2013 Prof Dr Andreas Mueller, Hochschule Rapperswil
 */
#include "point.h"
#include "pointcloud.h"
#include "lr.h"
#include "pca.h"
#include "image.h"

#include <cstdio>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <fstream>

double	angle(const double t) {
	double	m = 1;
	if (t != 0) {
		m = 1 + exp(1 - 1/fabs(t));
	}
	return M_PI * 0.5 * m;
}

double	angle2(const double t) {
	return M_PI * 0.5 * (1 + t * t * t);
}

int	main(int argc, char *argv[]) {
	pointgenerator	pg(10, 1.5);
	pointcloud_t	data = pg(10);
	data = data - center(data);

	double	step = 0.005;
	int	counter = 0;
	for (double t = -1; t < 1; t += step) {
		double	a = angle2(t);
		rotation	rot(a);
		std::cout << a << ": ";
		pointcloud_t	rotated_data = rot * data;
		lr	l(rotated_data);
		std::cout << l.a() << ", ";
		pca	p(rotated_data);
		std::cout << p.v1();
		std::cout << std::endl;
		char	filename[32];
		snprintf(filename, sizeof(filename), "images/i%04d.mp",
			counter++);
	
		std::ofstream	f(filename);
		f << image(rotated_data, l, p);
		f.close();
	}

	return EXIT_SUCCESS;
}
