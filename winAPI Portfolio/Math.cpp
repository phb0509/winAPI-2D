#include "Framework.h"


int Math::Random(int min, int max)
{
	return rand() % (max - min) + min;
}

double Math::Random(double min, double max)
{
	double random = (double)rand() / (double)RAND_MAX;//0~1사이의 랜덤 숫자

	return min + (max - min) * random;
}

Point Math::RandomPoint(double min, double max)
{
	return Point(Random(min, max), Random(min, max));
}
