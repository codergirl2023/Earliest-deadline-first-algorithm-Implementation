#include"Header.h"


float randNo(float min, float max) {
	float scale = rand() / (float)RAND_MAX;
	scale = min + scale * (max - min);
	scale= (ceilf(scale*100)/100);                                 //restricting to two places of decimal
	//cout << "\nrand=" << scale;
	return scale;
}