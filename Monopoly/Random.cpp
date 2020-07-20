#include "Random.h"
#include <stdlib.h>
#include <time.h>

void Random::Init() {

	srand(time(0));
	rand();

}

int Random::Integer(int min, int max_exclusive) {

	double normalized = (double)rand() / RAND_MAX;

	return (int)((max_exclusive - min) * normalized) + min;

}