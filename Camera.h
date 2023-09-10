
#ifndef _CAMERA_H_
#define _CAMERA_H_

class Camera
{
public:
	static int x;
	static int y;

	static int clamp(int val, int minVal, int maxVal);
};

#endif // !_CAMERA_H_