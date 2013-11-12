#
# Makefile -- build the demo program for PCA vs linear regression
#
# (c) 2013 Prof Dr Andreas Mueller, Hochschule Rapperswil
#
all:	lrpca

liblrpca.a:	lr.o pca.o pointcloud.o point.o
	ar cr liblrpca.a lr.o pca.o pointcloud.o point.o

lr.o:	lr.cpp lr.h pointcloud.h point.h
	g++ -Wall -O2 -g -o lr.o -c lr.cpp

pca.o:	pca.cpp pca.h pointcloud.h point.h
	g++ -Wall -O2 -g -o pca.o -c pca.cpp

pointcloud.o:	pointcloud.cpp pointcloud.h point.h
	g++ -Wall -O2 -g -o pointcloud.o -c pointcloud.cpp

point.o:	point.cpp point.h
	g++ -Wall -O2 -g -o point.o -c point.cpp

lrpca:	lrpca.cpp liblrpca.a
	g++ -Wall -O2 -g -o lrpca lrpca.cpp liblrpca.a
