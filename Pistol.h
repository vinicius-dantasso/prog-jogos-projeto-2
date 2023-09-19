
#ifndef _PISTOL_H_
#define _PISTOL_H_

#include "Object.h"
#include "Sprite.h"
#include "Timer.h"

class Pistol : public Object
{
private:
	Sprite * sprite;
	Timer  * timer;

public:
	Pistol();
	~Pistol();

	void Update();
	void Draw();
};

#endif // !_PISTOL_H_
