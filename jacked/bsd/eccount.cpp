/*
 * eccount.cpp -- counting points on an elliptic curve mod p
 *
 * (c) 2013 Prof Dr Andreas Mueller Hochschule Rapperswil
 */
#include <string>
#include <set>
#include <iostream>
#include <sstream>
#include <getopt.h>
#include <limits>
#include <stdlib.h>

int	debug = 0;

/**
 * \brief Class encapsulating an elliptic curve
 */
class EllipticCurve {
public:
	unsigned long	a;
	unsigned long	b;
	EllipticCurve(unsigned long _a, unsigned long _b) : a(_a), b(_b) { }
	std::string	toString() const {
		std::ostringstream	out;
		out << "a = " << a << ", b = " << b;
		return out.str();
	}
	/**
 	 * \brief Compute right hand side of elliptic curve equation
	 * This is used for 
 	 */
	unsigned long	rhsModP(unsigned long x, unsigned long p) const {
		unsigned long	v = (x * x) % p;
		v = (x * v) % p;
		v = (v + a * x) % p;
		v = (v + b) % p;
		return v;
	}
};

/**
 * \brief Functor implementing a point counting algorithm
 */
class CountModP {
	unsigned long	p;
public:
	CountModP(unsigned long _p) : p(_p) { }
	unsigned long	operator()(const EllipticCurve& curve) const;
};

typedef	std::set<unsigned long>	squareset;

/**
 * \brief Count points on an elliptic curve
 *
 * This method counts points on an elliptic curve by first assembling
 * a set of squares. The array squares contains the number of values
 * that yield a given square. Many of the array elements are zero, many
 * others are 2. Then it computes the right hand side of the elliptic
 * curve for every possible x value and checks whether the result is
 * a square, by checking the value in the squares array.
 * \param curve	the elliptic curve to count.
 */
unsigned long	CountModP::operator()(const EllipticCurve& curve) const {
	unsigned int	squares[p];
	for (int s = 0; s < p; s++) { squares[s] = 0; }

	// first compute modular squares for all integers mod p
	for (unsigned long y = 0; y < p; y++) {
		unsigned long s = (y * y) % p;
		squares[s]++;
	}

	// now go through the x values
	unsigned int	counter = 0;
	for (unsigned long x = 0; x < p; x++) {
		unsigned long	v = curve.rhsModP(x, p);
		counter += squares[v];
	}

	return counter + 1; // don't forget point at infinity
}

/**
 * \brief Primetester
 */
class PrimeTester {
public:
	bool	operator()(unsigned long n) const;
};

/**
 * \brief Primitive primality test function
 *
 * This function uses trial division, which is acceptable for small primes,
 * i.e. for the numbers we work with in the experiments here.
 */
bool	PrimeTester::operator()(unsigned long n) const {
	if (!(n & 0x1)) {
		return false;
	}
	unsigned long	divisor = 3;
	while ((divisor * divisor) < n) {
		if (0 == (n % divisor)) {
			return false;
		}
		divisor += 2;
	}
	return true;
}


/**
 * \brief compute the number of points on the elliptic curve
 *
 * \param p	prime to use for the computation. The function does not
 *		verify that p is in fact prime
 */
unsigned long	Np(unsigned long p) {
	EllipticCurve	curve(p - 5, 0);
	CountModP	counter(p);
	return counter(curve);
}

/**
 * \brief Process a single prime
 *
 * Compute Np and display the results
 * \param p	prime 
 */
void	do_Np(unsigned long p) {
	std::cout << p << "," << Np(p) << std::endl;
}

/**
 * \brief Main function
 */
int	main(int argc, char *argv[]) {
	unsigned long	limit = 1000;
	int	c;
	
	while (EOF != (c = getopt(argc, argv, "d")))
		switch (c) {
		case 'd':
			debug++;
			break;
		}

	if (optind < argc) {
		limit = atoi(argv[optind]);
	}

	// find out how many bits the limit has, we nee this to warn
	// the user that computation will be unreliable due to overflows
	int	bits = 0;
	unsigned long	l = limit;
	while (l) {
		l >>= 1;
		bits++;
	}
	if (2 * bits >= std::numeric_limits<unsigned long>::digits) {
		std::cerr << "your unsigned long type is not large enough for the computations" << std::endl;
		std::cerr << "modulo the larger primes in the range up to " << limit << " that you" << std::endl;
		std::cerr << " requested. Please choose a smaller limit." << std::endl;
		exit(EXIT_FAILURE);
	}

	do_Np(2);
	do_Np(3);
	do_Np(5);
	do_Np(7);
	unsigned long	p = 11;
	PrimeTester	isprim;
	while (p < limit) {
		if (isprim(p)) {
			do_Np(p);
		}
		p += 2;
	}

	exit(EXIT_SUCCESS);
}
