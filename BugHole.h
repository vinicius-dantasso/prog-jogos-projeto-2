
#ifndef _BUG_HOLE_H_
#define _BUG_HOLE_H_

#include "Object.h"
#include "Types.h"
#include "Animation.h"
#include "Timer.h"

enum HoleState {CHASING, BENEATHPLAYER};
enum HoleAnim {CLOSED, OPENNED};

class BugHole : public Object
{
private:
	TileSet* tile;
	Animation* anim;
	Timer* timer;

	float spd;
	float hSpd;
	float vSpd;
	float destX;
	float destY;

public:
	uint state;
	uint animState;

	BugHole(float posX, float posY);
	~BugHole();

	void ChasingPlayer();
	void BeneathPlayer();

	void OnCollision(Object* obj);
	void Update();
	void Draw();
};

#endif // !_BUG_HOLE_H_
