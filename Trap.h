
#ifndef _TRAP_H_
#define _TRAP_H_

#include "Types.h"
#include "Object.h"
#include "Animation.h"
#include "Timer.h"

class Trap : public Object
{
private:
	TileSet   * tile;
	Animation * anim;
	Timer	  * timer;

public:
	Trap(float posX, float posY);
	~Trap();
};

#endif // !_TRAP_H_
