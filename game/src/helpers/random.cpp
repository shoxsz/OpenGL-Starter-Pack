#include "random.hpp"

#include <ctime>
#include <cstdlib>

void Random::init(){
	srand(time(NULL));
}

float Random::random(float min, float max){
	int m = (int)((max - min) * 2000);
	int r = rand() % m;
	
	return r * (max / m);
}