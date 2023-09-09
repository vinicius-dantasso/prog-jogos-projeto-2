
#include "Camera.h"

int Camera::x = 0;
int Camera::y = 0;

int Camera::clamp(int val, int minVal, int maxVal)
{
	if (val < minVal)
		val = minVal;

	if (val > maxVal)
		val = maxVal;

	return val;
}