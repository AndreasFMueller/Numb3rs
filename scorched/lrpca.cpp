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

#include <cstdio>
#include <cstdlib>
#include <vector>
#include <iostream>

int	main(int argc, char *argv[]) {
	pointgenerator	pg(10, 0.5);
	pointcloud_t	data = pg(100);
	data = data - center(data);

	point_t	c = center(data);
	std::cout << c << std::endl;

	for (double angle = 0; angle < 3; angle += 0.1) {
		rotation	rot(angle);
		pointcloud_t	rotated_data = rot * data;
		lr	l(rotated_data);
		std::cout << l;
		pca	p(rotated_data);
		std::cout << p;
		std::cout << "scalar product: " << p.v1() * p.v2() << std::endl;
	}

	return EXIT_SUCCESS;
}
