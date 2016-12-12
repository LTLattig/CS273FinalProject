#pragma once
#ifndef RANDOM_
#define RANDOM_
#include <cstdlib>
#include <ctime>

/* Code Used from Airport Simulation Project
 * Whitworth Univerity
 * CS 273
 */
class Random {

public:

	/** Initializes the random number generator using the time
	as the seed.
	*/
	Random() {
		srand((unsigned int)std::time(NULL));
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