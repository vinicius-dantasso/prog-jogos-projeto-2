
#include "Scripts.h"
#define _USE_MATH_DEFINES
#include <cmath>

float Scripts::lengthdir_x(float len, float dir)
{
	float angle = dir * (M_PI / 180.0f);
	return len * cos(angle);
}

float Scripts::lengthdir_y(float len, float dir)
{
	float angle = dir * (M_PI / 180.0f);
	return len * sin(angle);
}

float Scripts::point_direction(float x1, float y1, float x2, float y2)
{
	float dx = x2 - x1;
	float dy = y2 - y1;

	float angle = atan2(dy, dx);
	angle = angle * (180.0f / M_PI);

	if (angle < 0)
		angle += 360.0f;

	return angle;
}