#include "Helper.h"

float radNormalize(float rad)
{
	float pi2 = 2 * M_PI;
	rad = fmod(rad, pi2);
	rad = fmod((rad + pi2), pi2);
	if( rad > M_PI)
	{
		rad = rad - M_PI;
	}
	return rad;
}

float DEGREES_TO_RADIANS(float _ANGLE)
{
	return _ANGLE * 0.01745329252;
}

float RADIANS_TO_DEGREES(float _ANGLE)
{
	return _ANGLE * 57.29577951;
}

