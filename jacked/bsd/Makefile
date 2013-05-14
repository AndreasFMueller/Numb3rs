#
# Makefile to count number of points in an elliptic curve
#
# (c) 2013 Prof Dr Andreas Mueller, Hochschule Rapperswil
#

# The constant N determines how large the primes to consider should be,
# all primes are smaller than N
N = 200000

all:	bsd.pdf

eccount:	eccount.cpp
	g++ -Wall -g -O2 -o eccount eccount.cpp

data.csv:	eccount Makefile
	./eccount $(N) > data.csv

bsd.pdf:	plots.R data.csv
	R --quiet --vanilla < plots.R
