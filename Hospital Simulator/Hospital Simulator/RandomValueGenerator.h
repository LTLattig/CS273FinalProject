#pragma once
#ifndef RANDOM_
#define RANDOM_
#include <cstdlib>
#include <ctime>

/** Class to encapsulate the standard random number generator. */
class Random {

public:

	/** Initializes the random number generator using the time
	as the seed.
	*/
	Random() {
		srand((unsigned int)std::time(0));
	}

	/** Initializes the random mumber generator using a
	supplied seed. 	*/
	Random(int seed) {
		srand(seed);
	}

	/** Returns a random integer in the range 0 – n. */
	int nextInt(int n) {
		return int(nextDouble() * n);
	}

	/** Return a random double in the range 0 – 1. */
	double nextDouble() {
		return double(rand()) / RAND_MAX;
	}

};
#endif