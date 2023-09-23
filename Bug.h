
#ifndef _BUG_H_
#define _BUG_H_

#include "Object.h"
#include "Types.h"
#include "Animation.h"
#include "Timer.h"

enum BugState {JUMPING, INSIDE, DELAY};
enum BugAnim {RISING, BUGHIT};

class Bug : public Object
{
private:
	TileSet   * tile;
	Animation * anim;
	Timer* timer;

	float spd;
	float hSpd;
	float vSpd;
	float grav;
	
	int life;
	int frames;
	int maxFrames;

	bool canJump;

public:
	uint state;
	uint animState;

	Bug(float posX, float posY);
	~Bug();

	int BugLife();
	void Inside();
	void Jumping();
	void Delay();

	void OnCollision(Object* obj);
	void Update();
	void Draw();
};

inline int Bug::BugLife()
{ return life; }

#endif // !_BUG_H_
